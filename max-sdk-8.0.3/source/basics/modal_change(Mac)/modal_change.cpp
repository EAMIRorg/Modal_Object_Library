/*
 *  modal_change.cpp
 *  modal_change
 *
 *  Created by Jonathan Bailey on 5/10/09, jonb@drumwell.net.
 *  Copyright 2009 VJ Manzo. All rights reserved.
 * 
 */

/* troublesome libs: MSVCRTD.lib, MSVCP90.DLL */

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "modal_change_constants.h"

#include <stdlib.h>
#include <string>
#include <map>
#include <vector>

// some nice boost algorithms/helpers
#include "boost/assign/std/vector.hpp"
#include "boost/algorithm/string.hpp"

using namespace std;
using namespace boost::assign;

typedef struct _modal_change 
{
	t_jbox u_box;						// header for UI objects
	
	// local storage
	string *m_note, *m_mode;

	// inlets and outlets
	// use a proxy for inlets, since we are accepting various types of inputs
	long m_in;							// space for the inlet number used by all the proxies
	void *m_proxy;						// inlets array - one proxy for notes and one for modes

	void *m_outlets[num_outlets];					// outlets array - 8 scale degrees + list outlet
	
	// attributes
	t_jrgba topcolor, bottomcolor, fontcolor;
} t_modal_change;

typedef map<string, int> t_note_map;
typedef map<string, vector<int> > t_mode_map;
typedef vector<vector<string> > t_scale_class_vec;

// globals for storing associations between note names and pitch values, and mode names and interval sequences
t_note_map g_note_map;
t_mode_map g_mode_map;
t_scale_class_vec g_scale_classes;

// api functions
void *modal_change_new(t_symbol *s, long argc, t_atom *argv);
void modal_change_free(t_modal_change *x);
void modal_change_paint(t_modal_change *x, t_object *patcherview);
void modal_change_assist(t_modal_change *x, void *b, long m, long a, char *s);
void modal_change_int(t_modal_change *x, long n);
void modal_change_anything(t_modal_change *x, t_symbol *s, long argc, t_atom *argv);
void modal_change_output(t_modal_change *x);


// helper functions
void modal_change_register_notevalues();
void modal_change_register_modevalues();
void modal_change_register_scaleclasses();
bool modal_change_determine_notevalue(string note_str);
void modal_change_determine_notename(int note, string *note_str);
bool modal_change_determine_modevalue(string mode);
bool modal_change_determine_modename(vector<int> *intervals, string *mode_str);
string modal_change_determine_scaleclass(string mode_str);

static t_class *s_modal_change_class;

int C74_EXPORT main()
{	
	t_class *c;
		
	c = class_new("modal_change", (method)modal_change_new, (method)modal_change_free, sizeof(t_modal_change), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, 0);

	// register handler functions
	class_addmethod(c, (method)modal_change_paint,		"paint",	A_CANT, 0);
	class_addmethod(c, (method)modal_change_assist,		"assist",	A_CANT, 0);
	class_addmethod(c, (method)modal_change_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)modal_change_anything,	"anything",	A_GIMME, 0);	
		
	// attributes
	char default_size[128];
	sprintf(default_size, "0. 0. %d. %d.", (int)(box_width_total)+1, (int)(box_height_total)+1); 
	CLASS_ATTR_DEFAULT(c,"patching_rect",0, default_size);			// define default size
	
	char top_default[128];
	sprintf(top_default, "%f %f %f %f", box_color1_r, box_color1_g, box_color1_b, box_color1_a);
	CLASS_ATTR_RGBA(c, "topcolor", 0, t_modal_change, topcolor);
	CLASS_ATTR_STYLE_LABEL(c, "topcolor", 0, "rgba", "Gradient color 1");
	CLASS_ATTR_SAVE(c, "topcolor", 0);
	CLASS_ATTR_DEFAULT(c, "topcolor", 0, top_default);
	
	char bott_default[128];
	sprintf(bott_default, "%f %f %f %f", box_color2_r, box_color2_g, box_color2_b, box_color2_a);
	CLASS_ATTR_RGBA(c, "bottomcolor", 0, t_modal_change, bottomcolor);
	CLASS_ATTR_STYLE_LABEL(c, "bottomcolor", 0, "rgba", "Gradient color 2");
	CLASS_ATTR_SAVE(c, "bottomcolor", 0);
	CLASS_ATTR_DEFAULT(c, "bottomcolor", 0, bott_default);

	char font_default[128];
	sprintf(font_default, "%f %f %f %f", font_color_r, font_color_g, font_color_b, font_color_a);
	CLASS_ATTR_RGBA(c, "fontcolor", 0, t_modal_change, fontcolor);
	CLASS_ATTR_STYLE_LABEL(c, "fontcolor", 0, "rgba", "Font color");
	CLASS_ATTR_SAVE(c, "fontcolor", 0);
	CLASS_ATTR_DEFAULT(c, "fontcolor", 0, font_default);
	
	
	// register global data variables
	modal_change_register_notevalues();
	modal_change_register_modevalues();
	modal_change_register_scaleclasses();
	
	class_register(CLASS_BOX, c);
	s_modal_change_class = c;

	return 0;
}

void modal_change_int(t_modal_change *x, long n)
{
	switch (proxy_getinlet((t_object *)x)) {
		case 0: 
		{
			// we have been called with a note name. check to see if it is valid
			if(n >= kNoteValueC && n <= kNoteValueB) {
				modal_change_determine_notename(n, x->m_note);
				// store the value and recompute new scale
				modal_change_output(x);
			} else { 
				post("modal_change: bad note ignored (%d)\n", n);
			}
		} break;
		default: break;
	}
}

void modal_change_anything(t_modal_change *x, t_symbol *s, long argc, t_atom *argv)
{
	string sym_value = s->s_name;
	boost::to_lower(sym_value);			// we store everything lower-case, for case insensitivity
	
	switch (proxy_getinlet((t_object *)x)) {
		case 0: 
		{
			// we have been called with a note name. check to see if it is valid
			if(modal_change_determine_notevalue(sym_value)) {
				// store the value and recompute new scale
				x->m_note->assign(sym_value);
				modal_change_output(x);
			} else { 
				post("modal_change: bad note ignored (%s)\n", s->s_name);
			}
		} break;
			
		case 1: 
		{
			// we have been called with either a mode name or an array of pitches.
			if(argc > 0) {
				// array of pitches - construct a vector out of the pitches and obtain mode name
				string mode = sym_value;
				vector<int> intervals;

				// take our best crack at filling the vector with the supplied intervals
				for(int i = 0; i < argc; i++) {
					t_atom *ap = argv + i; 
					if(atom_gettype(ap) == A_LONG)
						intervals.push_back((int)atom_getlong(ap));
				}
				
				if(modal_change_determine_modename(&intervals, &mode)) {
					x->m_mode->assign(mode);
					modal_change_output(x);
				} else {
					post("modal_change: bad interval sequence ignored\n");					
				}
				
			} else {
				// mode name
				if(modal_change_determine_modevalue(sym_value)) { 
					x->m_mode->assign(sym_value);
					modal_change_output(x);
				} else { 
					post("modal_change: bad mode ignored (%s)\n", s->s_name);
				}
			}
		} break;
		default: break;
	}
}

void modal_change_paint(t_modal_change *x, t_object *patcherview)
{
	t_rect rect;
	t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(patcherview);		// obtain graphics context
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	
	// draw rectangles
	float height = rect.height, width = rect.width;
	
	// top section + gradient
	t_jpattern *pat = jgraphics_pattern_create_linear (0., 0., 0., box_height_root*height);
	jgraphics_pattern_add_color_stop_rgba (pat, 0, x->topcolor.red, x->topcolor.green, x->topcolor.blue, x->topcolor.alpha);
	jgraphics_pattern_add_color_stop_rgba (pat, 1., x->bottomcolor.red, x->bottomcolor.green, x->bottomcolor.blue, x->bottomcolor.alpha);
	jgraphics_set_source (g, pat);
	jgraphics_rectangle(g, 0., 0., box_width_root*width, box_height_root*height);
	jgraphics_rectangle(g, box_width_root*width, 0., box_width_mode*width, box_height_mode*height);
	jgraphics_path_roundcorners(g, box_corner_radius*(height/box_height_total));
	jgraphics_fill (g);
	jgraphics_pattern_destroy (pat);
	
	// bottom section + gradient
	pat = jgraphics_pattern_create_linear (0., box_height_root*height, 0., (box_height_root+box_height_desc)*height);
	jgraphics_pattern_add_color_stop_rgba (pat, 0, x->topcolor.red, x->topcolor.green, x->topcolor.blue, x->topcolor.alpha);
	jgraphics_pattern_add_color_stop_rgba (pat, 1., x->bottomcolor.red, x->bottomcolor.green, x->bottomcolor.blue, x->bottomcolor.alpha);
	jgraphics_set_source (g, pat);
	jgraphics_rectangle(g, 0., box_height_root*height, box_width_intervals*width, box_height_intervals*height);	
	jgraphics_rectangle(g, box_width_intervals*width, box_height_root*height, box_width_desc*width, box_height_desc*height);	
	jgraphics_path_roundcorners(g, box_corner_radius*(box_height_total/height));
	jgraphics_fill(g);
	
	// draw top text
	double curr_w, curr_h, last_w, last_h;
	
	last_w = last_h = 0.;
	char *text = (char*)malloc(sizeof(char) * (x->m_note->length() + 1));
	sprintf(text, x->m_note->c_str());
	text[0] = toupper(text[0]);
	jgraphics_set_source_rgba(g, x->fontcolor.red, x->fontcolor.green, x->fontcolor.blue, x->fontcolor.alpha);
	jgraphics_select_font_face(g, font_face, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL);
	jgraphics_set_font_size(g, font_size_large*(height/box_height_total));
	jgraphics_text_measure(g, text, &curr_w, &curr_h);
	jgraphics_move_to(g, last_w + text_offset_x*width, last_h + curr_h + text_offset_y*height);
	jgraphics_show_text(g, text);
	free(text);
	
	last_w = box_width_root*width;
	int len = x->m_mode->length();
	text = (char*)malloc(sizeof(char) * (len + 1));
	sprintf(text, x->m_mode->c_str());
	text[0] = toupper(text[0]);
	for(int i = 0; i < len; i++) if(text[i] == '_') text[i] = ' ';		// replace any underscores with spaces
	jgraphics_text_measure(g, text, &curr_w, &curr_h);
	jgraphics_move_to(g, last_w + text_offset_x*width, last_h + curr_h + text_offset_y*height);
	jgraphics_show_text(g, text);
	free(text);

	// draw bottom text
	jgraphics_set_font_size(g, font_size_small*(height/box_height_total));

	// create a new string out of the intervals 
	string intervals = "Degree_distances: ";
	if(strcmp(text, default_string) == 0) {
		// we don't have a mode assigned yet
		intervals += default_string;
	} else {
		// we have a mode
		vector<int> vec = g_mode_map[*(x->m_mode)];

		vector<int>::iterator it;
		for(it = vec.begin(); it != vec.end(); it++) {
			char tmp[8];
			sprintf(tmp, "%d ", *it);
			intervals += tmp;		
		}
	}
	
	last_w = 0; last_h = box_height_root*height;
	text = (char *)intervals.c_str();
	jgraphics_text_measure(g, text, &curr_w, &curr_h);
	jgraphics_move_to(g, last_w + text_offset_x*width, last_h + curr_h);
	jgraphics_show_text(g, text);
	
	last_w = box_width_intervals*width; last_h = box_height_root*height;
	string desc = modal_change_determine_scaleclass(*(x->m_mode));
	text = (char *)desc.c_str();
	jgraphics_text_measure(g, text, &curr_w, &curr_h);
	jgraphics_move_to(g, last_w + text_offset_x*width, last_h + curr_h);
	jgraphics_show_text(g, text);
}

void modal_change_assist(t_modal_change *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) {	// Inlets
        switch (a) {
            case 0: sprintf(s, "Tonic - note name (symbol) or pitch class value (int)"); break;
			case 1: sprintf(s, "Mode - mode name (symbol) or pitch intervals (list)"); break;
        }
    }
    else {						// Outlets
        switch (a) {
            case 0: sprintf(s, "Scale degree 1 (tonic)"); break;
            case 8: sprintf(s, "Interval list"); break;
			default: sprintf(s, "Scale degree %ld", a+1); break;
        }
    } 
}

void modal_change_free(t_modal_change *x)
{
	sysmem_freeptr(x->m_note);
	sysmem_freeptr(x->m_mode);
	jbox_free((t_jbox *)x);
}

void *modal_change_new(t_symbol *s, long argc, t_atom *argv)
{
	t_modal_change *x = NULL;
	long boxflags;
	t_dictionary *d=NULL;
	
	if (!(d=object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_modal_change *)object_alloc(s_modal_change_class);
	boxflags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_NODRAWBOX
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT	
	//		| JBOX_NOGROW
	//		| JBOX_GROWY
			| JBOX_GROWBOTH
	//		| JBOX_HILITE
	//		| JBOX_BACKGROUND
			| JBOX_DRAWBACKGROUND
	//		| JBOX_NOFLOATINSPECTOR
	//		| JBOX_TEXTFIELD
	//		| JBOX_MOUSEDRAGDELTA
	//		| JBOX_TEXTFIELD
			;

	jbox_new((t_jbox *)x, boxflags, argc, argv);

	// create the proxy for the second inlet
	x->m_proxy = proxy_new((t_object *)x, 1, &x->m_in);

	// allow the object to accept messages in the first inlet 
	x->u_box.b_firstin = (t_object*) x; 
	
	// create some outlets
	x->m_outlets[(num_outlets-1)] = listout(x);
	for(int i = (num_outlets-2); i >= 0; i--)
		x->m_outlets[i] = intout(x);
	
	// allocate memory for the locates and initialize
	void *memory = (void *) sysmem_newptr(sizeof(string));
	x->m_note = new(memory) string;

	memory = (void *) sysmem_newptr(sizeof(string));
	x->m_mode = new(memory) string;
	
	x->m_note->assign(default_string);
	x->m_mode->assign(default_string);
	
	post("Modal Object Library (c) 2006 V.J. Manzo");
	post("www.vjmanzo.com/mol");
		
	jbox_ready((t_jbox *)x);
	attr_dictionary_process(x, d);

	return x;
}

void modal_change_output(t_modal_change *x) {
	// determine the current note value and add pitch offsets to that value 
	t_atom argv[num_outlets-1];

	if((x->m_note->compare(default_string) == 0) || (x->m_mode->compare(default_string) == 0)) return;
	
	int root = g_note_map[*(x->m_note)];	
	vector<int> vec = g_mode_map[*(x->m_mode)];

	// compute offsets for defined intervals based on tonic
	long val = root;
	atom_setlong(argv, val);
	outlet_int(x->m_outlets[0], val);
	
	for (int i = 1; i < num_outlets-1; i++) {
		val += vec[i-1];
		atom_setlong(argv + i, val);
		outlet_int(x->m_outlets[i], val);
	}
	
	outlet_list(x->m_outlets[num_outlets-1], NULL, num_outlets-1, argv);

	// repaint the interface
	jbox_redraw(&x->u_box);
}

// some helper functions

void modal_change_register_notevalues() {
	// create a map of note names and note values
	g_note_map[name_C]	= kNoteValueC; 
	g_note_map[name_Cs]	= kNoteValueCs; 
	g_note_map[name_Db]	= kNoteValueCs; 
	g_note_map[name_D]	= kNoteValueD; 
	g_note_map[name_Ds]	= kNoteValueDs; 
	g_note_map[name_Eb]	= kNoteValueDs; 
	g_note_map[name_E]	= kNoteValueE; 
	g_note_map[name_F]	= kNoteValueF; 
	g_note_map[name_Fs]	= kNoteValueFs; 
	g_note_map[name_Gb]	= kNoteValueFs; 
	g_note_map[name_G]	= kNoteValueG; 
	g_note_map[name_Gs]	= kNoteValueGs; 
	g_note_map[name_Ab]	= kNoteValueGs; 
	g_note_map[name_A]	= kNoteValueA; 
	g_note_map[name_As]	= kNoteValueAs; 
	g_note_map[name_Bb]	= kNoteValueAs; 
	g_note_map[name_B]	= kNoteValueB; 
}

void modal_change_register_modevalues() {
	// take advantage of some niceties in boost's vector extensions 
	// to elegantly initialize our map of note vectors
	g_mode_map[name_major]				+= scale_ionian;
	g_mode_map[name_ionian]				+= scale_ionian;
	g_mode_map[name_dorian]				+= scale_dorian;				
	g_mode_map[name_phrygian]			+= scale_phrygian;			
	g_mode_map[name_lydian]				+= scale_lydian;				
	g_mode_map[name_mixolydian]			+= scale_mixolydian;			
	g_mode_map[name_minor]				+= scale_aeolian;			
	g_mode_map[name_aeolian]			+= scale_aeolian;			
	g_mode_map[name_locrian]			+= scale_locrian;			
	g_mode_map[name_harmonic_major]		+= scale_harmonic_major;		
	g_mode_map[name_dorian_b5]			+= scale_dorian_b5;			
	g_mode_map[name_phrygian_b4]		+= scale_phrygian_b4;		
	g_mode_map[name_lydian_b3]			+= scale_lydian_b3;			
	g_mode_map[name_mixolydian_b2]		+= scale_mixolydian_b2;		
	g_mode_map[name_aeolian_b1]			+= scale_aeolian_b1;			
	g_mode_map[name_locrian_b7]			+= scale_locrian_b7;			
	g_mode_map[name_harmonic_minor]		+= scale_harmonic_minor;		
	g_mode_map[name_locrian_s6]			+= scale_ionian_s5;			
	g_mode_map[name_ionian_s5]			+= scale_ionian_s5;			
	g_mode_map[name_dorian_s4]			+= scale_dorian_s4;			
	g_mode_map[name_phrygian_s3]		+= scale_phrygian_s3;		
	g_mode_map[name_lydian_s2]			+= scale_lydian_s2;			
	g_mode_map[name_mixolydian_s1]		+= scale_mixolydian_s1;		
	g_mode_map[name_melodic_minor]		+= scale_melodic_minor;		
	g_mode_map[name_dorian_b2]			+= scale_dorian_b2;			
	g_mode_map[name_lydian_s5]			+= scale_lydian_s5;			
	g_mode_map[name_lydian_b7]			+= scale_lydian_b7;			
	g_mode_map[name_mixolydian_b6]		+= scale_mixolydian_b6;		
	g_mode_map[name_locrian_s2]			+= scale_locrian_s2;			
	g_mode_map[name_locrian_b4]			+= scale_locrian_b4;
	g_mode_map[name_pentatonic_1]		+= scale_pentatonic_1;
	g_mode_map[name_pentatonic_2]		+= scale_pentatonic_2;
	g_mode_map[name_pentatonic_3]		+= scale_pentatonic_3;
	g_mode_map[name_pentatonic_4]		+= scale_pentatonic_4;
	g_mode_map[name_pentatonic_5]		+= scale_pentatonic_5;
}
void modal_change_register_scaleclasses() {	
	g_scale_classes.resize(5);
	
	g_scale_classes[0] += major_modes;
	g_scale_classes[1] += harmonic_major_modes;
	g_scale_classes[2] += melodic_minor_modes;
	g_scale_classes[3] += harmonic_minor_modes;
    g_scale_classes[4] += pentatonic_modes;
}


bool modal_change_determine_notevalue(string note_str) {
	t_note_map::iterator it = g_note_map.find(note_str);
	return (it != g_note_map.end());
}

void modal_change_determine_notename(int note, string *note_str) {
	t_note_map::iterator it;
	for(it = g_note_map.begin(); it != g_note_map.end(); it++) {
		if(it->second == note) { 
			note_str->assign(it->first);
			break;
		}
	}
}

bool modal_change_determine_modevalue(string mode) {
	t_mode_map::iterator it = g_mode_map.find(mode);
	return(it != g_mode_map.end());
}

bool modal_change_determine_modename(vector<int> *intervals, string *mode_str) {
	t_mode_map::iterator it;
	for(it = g_mode_map.begin(); it != g_mode_map.end(); it++) {
		if(std::equal(intervals->begin(), intervals->end(), it->second.begin())) { 
			mode_str->assign(it->first);
			break;
		}
	}
	return(it != g_mode_map.end());
}

string modal_change_determine_scaleclass(string mode_str) {
	string result = "";
	char buffer[64];
	
	// major modes
	vector<string> next = g_scale_classes[0];
	int len = next.size();	
	for(int i = 0; i < len; i++) {
		if(next[i].compare(mode_str) == 0) {
			sprintf(buffer, text_major_modes, (i+1));
			result = buffer;
			goto finish;
		}
	}
	
	// harmonic major modes
	next = g_scale_classes[1];
	len = next.size();
	for(int i = 0; i < len; i++) {
		if(next[i].compare(mode_str) == 0) {
			sprintf(buffer, text_harmonic_major_modes, (i+1));
			result = buffer;
			goto finish;
		}
	}

	// melodic minor modes
	next = g_scale_classes[2];
	len = next.size();
	for(int i = 0; i < len; i++) {
		if(next[i].compare(mode_str) == 0) {
			sprintf(buffer, text_melodic_minor_modes, (i+1));
			result = buffer;
			goto finish;
		}
	}

	// harmonic minor modes
	next = g_scale_classes[3];
	len = next.size();
	for(int i = 0; i < len; i++) {
		if(next[i].compare(mode_str) == 0) {
			sprintf(buffer, text_harmonic_minor_modes, (i+1));
			result = buffer;
			goto finish;
		}
	}
    
    // pentatonic modes
    next = g_scale_classes[4];
    len = next.size();
    for(int i = 0; i < len; i++) {
        if(next[i].compare(mode_str) == 0) {
            sprintf(buffer, text_pentatonic_modes, (i+1));
            result = buffer;
            goto finish;
        }
    }
	
	if(mode_str.compare(name_major) == 0) {
		result += "mode 1 of the major scale";
		goto finish;
	}
	
	if(mode_str.compare(name_minor) == 0) {
		result += "mode 6 of the major scale";
		goto finish;
	}
	
	
	
finish:
	return result;
}


// a function to construct some hash tables
