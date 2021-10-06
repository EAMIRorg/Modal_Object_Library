/*
 *  modal_triad.cpp
 *  modal_triad
 *
 *  Copyright 2009 VJ Manzo. All rights reserved.
 * 
 */

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "modal_triad_constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>

typedef struct _modal_triad 
{
	t_object	ob;						// object header
	// inlets and outlets
	void *m_outlets[num_outlets];		// outlets array - 8 scale degrees + list outlet
	
	// members
	t_symbol *m_chord;					// chord name
	int	*m_pitches;						// pitches
	bool m_modulus;						// take modulus?
} t_modal_triad;

// globals for storing associations between chord names and pitch values
t_hashtab *g_named_chords;				// named chords -> C, d#, g0, etc
t_hashtab *g_diatonic_chords;			// diatonic chords -> I, ii, etc 


// api functions
void *modal_triad_new(t_symbol *s, long argc, t_atom *argv);
void modal_triad_free(t_modal_triad *x);
void modal_triad_assist(t_modal_triad *x, void *b, long m, long a, char *s);
void modal_triad_int(t_modal_triad *x, long n);
void modal_triad_anything(t_modal_triad *x, t_symbol *s, long argc, t_atom *argv);
void modal_triad_output(t_modal_triad *x);

void modal_triad_in1(t_modal_triad *x, long n);
void modal_triad_in2(t_modal_triad *x, long n);
void modal_triad_in3(t_modal_triad *x, long n);
void modal_triad_in4(t_modal_triad *x, long n);
void modal_triad_in5(t_modal_triad *x, long n);
void modal_triad_in6(t_modal_triad *x, long n);
void modal_triad_in7(t_modal_triad *x, long n);
void modal_triad_in8(t_modal_triad *x, long n);
void modal_triad_in9(t_modal_triad *x, long n);


// helper functions
void modal_triad_addchord(t_hashtab *hash, t_symbol *name, int *notes);
void modal_triad_register_named_chords();
void modal_triad_register_diatonic_chords();
void modal_triad_update_pitch(t_modal_triad *x, int degree, int value);
void modal_triad_update_chromatics(t_modal_triad *x); 

static t_class *s_modal_triad_class;

int C74_EXPORT main()
{	
	t_class *c;
		
	c = class_new("modal_triad", (method)modal_triad_new, (method)modal_triad_free, sizeof(t_modal_triad), 0L, A_GIMME, 0);

	// register handler functions
	class_addmethod(c, (method)modal_triad_assist,		"assist",	A_CANT, 0);
	class_addmethod(c, (method)modal_triad_int,			"int",		A_LONG, 0);
	class_addmethod(c, (method)modal_triad_anything,	"anything",	A_GIMME, 0);	
	class_addmethod(c, (method)modal_triad_in1,			"in1",		A_LONG, 0);
	class_addmethod(c, (method)modal_triad_in2,			"in2",		A_LONG, 0);
	class_addmethod(c, (method)modal_triad_in3,			"in3",		A_LONG, 0);
	class_addmethod(c, (method)modal_triad_in4,			"in4",		A_LONG, 0);
	class_addmethod(c, (method)modal_triad_in5,			"in5",		A_LONG, 0);
	class_addmethod(c, (method)modal_triad_in6,			"in6",		A_LONG, 0);
	class_addmethod(c, (method)modal_triad_in7,			"in7",		A_LONG, 0);
	class_addmethod(c, (method)modal_triad_in8,			"in8",		A_LONG, 0);
	class_addmethod(c, (method)modal_triad_in9,			"in9",		A_LONG, 0);
		
	class_register(CLASS_BOX, c);
	s_modal_triad_class = c;

	return 0;
}

void modal_triad_int(t_modal_triad *x, long n)
{
	switch (proxy_getinlet((t_object *)x)) {
		case 0: 
		{
			char num[128];
			sprintf(num, "%ld", n);
			x->m_chord = gensym(num);
			modal_triad_output(x);
		} break;
	}
}

void modal_triad_anything(t_modal_triad *x, t_symbol *s, long argc, t_atom *argv)
{
	switch (proxy_getinlet((t_object *)x)) {
		case 0: 
		{
			// assign chord name and output
			x->m_chord = s;
			modal_triad_output(x);
		} break;
	}			
}



void modal_triad_update_pitch(t_modal_triad *x, int degree, int value) 
{
	// update the pitches themselves
	for(int i = 0; i <= 28; i+= 7) {
		x->m_pitches[degree + i] = value;
		value += 12;
	}
	modal_triad_update_chromatics(x); 
}

void modal_triad_update_chromatics(t_modal_triad *x) 
{
	for(int i = 0; i < 7; i++) x->m_pitches[chromatic1 + i] = (x->m_pitches[deg1 + i] + x->m_pitches[deg2 + i])/2;
	for(int i = 0; i < 7; i++) x->m_pitches[chromatic8 + i] = (x->m_pitches[deg1 + i] + x->m_pitches[deg9 + i])/2;
}


void modal_triad_in1(t_modal_triad *x, long n) 
{
	x->m_modulus = (bool)n;
}

void modal_triad_in2(t_modal_triad *x, long n) 
{
	modal_triad_update_pitch(x, deg1, n);
}

void modal_triad_in3(t_modal_triad *x, long n) 
{
	modal_triad_update_pitch(x, deg2, n);
}

void modal_triad_in4(t_modal_triad *x, long n) 
{
	modal_triad_update_pitch(x, deg3, n);
}

void modal_triad_in5(t_modal_triad *x, long n)
{
	modal_triad_update_pitch(x, deg4, n);
}

void modal_triad_in6(t_modal_triad *x, long n) 
{
	modal_triad_update_pitch(x, deg5, n);
}

void modal_triad_in7(t_modal_triad *x, long n) 
{
	modal_triad_update_pitch(x, deg6, n);
}

void modal_triad_in8(t_modal_triad *x, long n) 
{
	modal_triad_update_pitch(x, deg7, n);
}

void modal_triad_in9(t_modal_triad *x, long n) 
{
	modal_triad_update_pitch(x, deg8, n);
}

void modal_triad_assist(t_modal_triad *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) {	// Inlets
        switch (a) {
            case 0: sprintf(s, "Chord name (symbol) or pitch class value (int)"); break;
			case 1: sprintf(s, "Switch (int) - take mod 12 of output"); break;
			default: sprintf(s, "Outlet %ld from modal_change", a-1); break;
        }
    }
    else {						// Outlets
        switch (a) {
			case 0: sprintf(s, "Root"); break;
			case 1: sprintf(s, "Third"); break;
			case 2: sprintf(s, "Fifth"); break;
			case 3: sprintf(s, "Seventh"); break;
			case 4: sprintf(s, "Ninth"); break;
			case 5: sprintf(s, "Eleventh"); break;
			case 6: sprintf(s, "Thirteeth"); break;
        }
    } 
}

void chord_free_fun(void *item)
{
	int *chord = (int*)item;
	if(chord) sysmem_freeptr(chord);
}


void modal_triad_free(t_modal_triad *x)
{
	if(x->m_pitches) sysmem_freeptr(x->m_pitches);
	if(g_named_chords) {
		hashtab_funall(g_named_chords, (method)chord_free_fun, NULL);
		sysmem_freeptr(g_named_chords);
	}
	if(g_diatonic_chords) {
		hashtab_funall(g_diatonic_chords, (method)chord_free_fun, NULL);
		sysmem_freeptr(g_diatonic_chords);
	}
}

void *modal_triad_new(t_symbol *s, long argc, t_atom *argv)
{
	t_modal_triad *x = NULL;
	x = (t_modal_triad *)object_alloc(s_modal_triad_class);

	// allocate memory for pitches
	x->m_pitches = (int*)sysmem_newptr(sizeof(int)*num_pitches);
	
	// zero out the memory
	memset(x->m_pitches, 0, sizeof(int)*num_pitches);
	
	// create inlets and outlets
	for(int i = num_inlets-1; i > 0; i--)
		intin(x, i);	

	for(int i = num_outlets-1; i >= 0; i--)
		x->m_outlets[i] = intout(x);
	
	x->m_chord = gensym("");
	x->m_modulus = false;
	
	
	// set up global data structures
	modal_triad_register_named_chords();
	modal_triad_register_diatonic_chords();
	
	// print banner
	post("Modal Object Library (c) 2006 V.J. Manzo");
	post("www.vjmanzo.com/mol");
		
	return x;
}

void modal_triad_output(t_modal_triad *x) {
	int output[num_outlets];
	if(x->m_chord == gensym("")) return;
	
	// copy the chord name
	int length = strlen(x->m_chord->s_name);
	char *chord_name = sysmem_newptr((length+1)*sizeof(char)); 
	strncpy(chord_name, x->m_chord->s_name, length);
	chord_name[length] = 0;
	

	char *strptr = chord_name, *result;
	// substitute any instance of dom7 in the string with b7
	while((result = strstr(strptr, "dom7"))) {
		int index = result - strptr;
		strncpy(result, "b7", 2);
		strncpy(result+2, result+4, length-index-3);
		length -= 2;
		strptr = result;
	}

	
	// search for alterations, from right to left
	// for eg: C#b5#13 
	int alterations[notes_per_scale];
	memset(alterations, 0, sizeof(int)*notes_per_scale);
	
	int end = length;
	char second_to_last, third_to_last, alt;
	int value, adjust;

	while(end >= 3) {
		// do we see a # or a b sign?
		second_to_last = chord_name[end-2];
		third_to_last = chord_name[end-3];
		
		if(second_to_last == '#' || third_to_last == '#' ||
		   second_to_last == 'b' || third_to_last == 'b') {
			// is it the second to last or third to last?
			if(second_to_last == '#' || second_to_last == 'b') {
				// second to last - one digit
				adjust = 2;
				alt = second_to_last;
				value = chord_name[end-1] - '0';
			} else {
				adjust = 3;
				alt = third_to_last;
				value = chord_name[end-1] - '0';
				value += 10*(second_to_last-'0');
			}
			
			// is this a valid number?
			if(value >= 1 && value <= 13) {
				if(value % 2) value--;		// is this an odd number?
				alterations[(value/2)] = (alt == '#') ? 1 : -1;
				end -= adjust;
			} else {
				break;
			}

		} else {
			break;
		}
	}
	
	// set the end of the chord string according to where we stopped looking for alterations
	chord_name[end] = 0;
	
	// first look up the chord in the named chords, and just output those values if found
	int *chord = NULL;
	hashtab_lookup(g_named_chords, gensym(chord_name), (t_object **)&chord);

	if(chord) {
		for(int i = 0; i < num_outlets; i++)
			output[i] = chord[i] + alterations[i];
	} else {
		hashtab_lookup(g_diatonic_chords, gensym(chord_name), (t_object **)&chord);		
	
		if(chord == NULL) { 
			post("modal_triad: invalid chord name");
			return;
		} else {
			for(int i = 0; i < num_outlets; i++)
				output[i] = x->m_pitches[chord[i*2]] + chord[i*2+1] + alterations[i];
		}
	}
	
	if(x->m_modulus)
		for(int i = 0; i < num_outlets; i++)
			output[i] = output[i] % 12;
	
	// output outputs
	for (int i = 0; i < num_outlets; i++) {
		outlet_int(x->m_outlets[i], output[i]);
	}	
}

// some helper functions
void modal_triad_addchord(t_hashtab *hash, t_symbol *name, int *notes, int num_notes) {
	int bytes = sizeof(int)*num_notes;
	int *notemem = (int *)sysmem_newptr(bytes);
	memcpy(notemem, notes, bytes);
	
	hashtab_store(hash, name, (t_object*)notemem);
}

void modal_triad_register_named_chords() {
	g_named_chords = (t_hashtab *) hashtab_new(70);
	
	// Major Letter Name Chord
	int chord_C[] = {Chord_C};
	modal_triad_addchord(g_named_chords, gensym("C"), chord_C, notes_per_scale);

	int chord_Cs[] = {Chord_Cs};
	modal_triad_addchord(g_named_chords, gensym("C#"), chord_Cs, notes_per_scale);

	int chord_Db[] = {Chord_Db};
	modal_triad_addchord(g_named_chords, gensym("Db"), chord_Db, notes_per_scale);
	
	int chord_D[] = {Chord_D};
	modal_triad_addchord(g_named_chords, gensym("D"), chord_D, notes_per_scale);
	
	int chord_Ds[] = {Chord_Ds};
	modal_triad_addchord(g_named_chords, gensym("D#"), chord_Ds, notes_per_scale);
	
	int chord_Eb[] = {Chord_Eb};
	modal_triad_addchord(g_named_chords, gensym("Eb"), chord_Eb, notes_per_scale);
	
	int chord_E[] = {Chord_E};
	modal_triad_addchord(g_named_chords, gensym("E"), chord_E, notes_per_scale);
	
	int chord_F[] = {Chord_F};
	modal_triad_addchord(g_named_chords, gensym("F"), chord_F, notes_per_scale);
	
	int chord_Fs[] = {Chord_Fs};
	modal_triad_addchord(g_named_chords, gensym("F#"), chord_Fs, notes_per_scale);
	
	int chord_Gb[] = {Chord_Gb};
	modal_triad_addchord(g_named_chords, gensym("Gb"), chord_Gb, notes_per_scale);
	
	int chord_G[] = {Chord_G};
	modal_triad_addchord(g_named_chords, gensym("G"), chord_G, notes_per_scale);
	
	int chord_Gs[] = {Chord_Gs};
	modal_triad_addchord(g_named_chords, gensym("G#"), chord_Gs, notes_per_scale);
	
	int chord_Ab[] = {Chord_Ab};
	modal_triad_addchord(g_named_chords, gensym("Ab"), chord_Ab, notes_per_scale);
	
	int chord_A[] = {Chord_A};
	modal_triad_addchord(g_named_chords, gensym("A"), chord_A, notes_per_scale);
	
	int chord_As[] = {Chord_As};
	modal_triad_addchord(g_named_chords, gensym("A#"), chord_As, notes_per_scale);
	
	int chord_Bb[] = {Chord_Bb};
	modal_triad_addchord(g_named_chords, gensym("Bb"), chord_Bb, notes_per_scale);
	
	int chord_B[] = {Chord_B};
	modal_triad_addchord(g_named_chords, gensym("B"), chord_B, notes_per_scale);
	
	//Minor Letter Name Chord
	int chord_c[] = {Chord_c};
	modal_triad_addchord(g_named_chords, gensym("c"), chord_c, notes_per_scale);
	
	int chord_cs[] = {Chord_cs};
	modal_triad_addchord(g_named_chords, gensym("c#"), chord_cs, notes_per_scale);
	
	int chord_db[] = {Chord_db};
	modal_triad_addchord(g_named_chords, gensym("db"), chord_db, notes_per_scale);
	
	int chord_d[] = {Chord_d};
	modal_triad_addchord(g_named_chords, gensym("d"), chord_d, notes_per_scale);
	
	int chord_ds[] = {Chord_ds};
	modal_triad_addchord(g_named_chords, gensym("d#"), chord_ds, notes_per_scale);
	
	int chord_eb[] = {Chord_eb};
	modal_triad_addchord(g_named_chords, gensym("eb"), chord_eb, notes_per_scale);
	
	int chord_e[] = {Chord_e};
	modal_triad_addchord(g_named_chords, gensym("e"), chord_e, notes_per_scale);
	
	int chord_f[] = {Chord_f};
	modal_triad_addchord(g_named_chords, gensym("f"), chord_f, notes_per_scale);
	
	int chord_fs[] = {Chord_fs};
	modal_triad_addchord(g_named_chords, gensym("f#"), chord_fs, notes_per_scale);
	
	int chord_gb[] = {Chord_gb};
	modal_triad_addchord(g_named_chords, gensym("gb"), chord_gb, notes_per_scale);
	
	int chord_g[] = {Chord_gs};
	modal_triad_addchord(g_named_chords, gensym("g"), chord_g, notes_per_scale);
	
	int chord_gs[] = {Chord_gs};
	modal_triad_addchord(g_named_chords, gensym("g#"), chord_gs, notes_per_scale);
	
	int chord_ab[] = {Chord_ab};
	modal_triad_addchord(g_named_chords, gensym("ab"), chord_ab, notes_per_scale);
	
	int chord_a[] = {Chord_a};
	modal_triad_addchord(g_named_chords, gensym("a"), chord_a, notes_per_scale);
	
	int chord_as[] = {Chord_as};
	modal_triad_addchord(g_named_chords, gensym("a#"), chord_as, notes_per_scale);
	
	int chord_bb[] = {Chord_bb};
	modal_triad_addchord(g_named_chords, gensym("bb"), chord_bb, notes_per_scale);
	
	int chord_b[] = {Chord_b};
	modal_triad_addchord(g_named_chords, gensym("b"), chord_b, notes_per_scale);
	
	//Diminished Letter Name  Chord	
	int chord_c0[] = {Chord_c0};
	modal_triad_addchord(g_named_chords, gensym("c0"), chord_c0, notes_per_scale);
	
	int chord_cs0[] = {Chord_cs0};
	modal_triad_addchord(g_named_chords, gensym("c#0"), chord_cs0, notes_per_scale);
	
	int chord_db0[] = {Chord_db0};
	modal_triad_addchord(g_named_chords, gensym("db0"), chord_db0, notes_per_scale);
	
	int chord_d0[] = {Chord_d0};
	modal_triad_addchord(g_named_chords, gensym("d0"), chord_d0, notes_per_scale);
	
	int chord_ds0[] = {Chord_ds0};
	modal_triad_addchord(g_named_chords, gensym("d#0"), chord_ds0, notes_per_scale);
	
	int chord_eb0[] = {Chord_eb0};
	modal_triad_addchord(g_named_chords, gensym("eb0"), chord_eb0, notes_per_scale);
	
	int chord_e0[] = {Chord_e0};
	modal_triad_addchord(g_named_chords, gensym("e0"), chord_e0, notes_per_scale);
	
	int chord_f0[] = {Chord_e0};
	modal_triad_addchord(g_named_chords, gensym("f0"), chord_f0, notes_per_scale);
	
	int chord_fs0[] = {Chord_fs0};
	modal_triad_addchord(g_named_chords, gensym("f#0"), chord_fs0, notes_per_scale);
	
	int chord_gb0[] = {Chord_fs0};
	modal_triad_addchord(g_named_chords, gensym("gb0"), chord_gb0, notes_per_scale);
	
	int chord_g0[] = {Chord_g0};
	modal_triad_addchord(g_named_chords, gensym("g0"), chord_g0, notes_per_scale);
	
	int chord_gs0[] = {Chord_gs0};
	modal_triad_addchord(g_named_chords, gensym("g#0"), chord_gs0, notes_per_scale);
	
	int chord_ab0[] = {Chord_ab0};
	modal_triad_addchord(g_named_chords, gensym("ab0"), chord_ab0, notes_per_scale);
	
	int chord_a0[] = {Chord_a0};
	modal_triad_addchord(g_named_chords, gensym("a0"), chord_a0, notes_per_scale);
	
	int chord_as0[] = {Chord_as0};
	modal_triad_addchord(g_named_chords, gensym("a#0"), chord_as0, notes_per_scale);
	
	int chord_bb0[] = {Chord_bb0};
	modal_triad_addchord(g_named_chords, gensym("bb0"), chord_bb0, notes_per_scale);
	
	int chord_b0[] = {Chord_b0};
	modal_triad_addchord(g_named_chords, gensym("b0"), chord_b0, notes_per_scale);
	
	// Augmented Letter Name Chord
	int chord_Cplus[] = {Chord_Cplus};
	modal_triad_addchord(g_named_chords, gensym("C+"), chord_Cplus, notes_per_scale);
	
	int chord_Csplus[] = {Chord_Csplus};
	modal_triad_addchord(g_named_chords, gensym("C#+"), chord_Csplus, notes_per_scale);
	
	int chord_Dbplus[] = {Chord_Dbplus};
	modal_triad_addchord(g_named_chords, gensym("Db+"), chord_Dbplus, notes_per_scale);
	
	int chord_Dplus[] = {Chord_Dplus};
	modal_triad_addchord(g_named_chords, gensym("D+"), chord_Dplus, notes_per_scale);
	
	int chord_Dsplus[] = {Chord_Dsplus};
	modal_triad_addchord(g_named_chords, gensym("D#+"), chord_Dsplus, notes_per_scale);
	
	int chord_Ebplus[] = {Chord_Ebplus};
	modal_triad_addchord(g_named_chords, gensym("Eb+"), chord_Ebplus, notes_per_scale);
	
	int chord_Eplus[] = {Chord_Eplus};
	modal_triad_addchord(g_named_chords, gensym("E+"), chord_Eplus, notes_per_scale);
	
	int chord_Fplus[] = {Chord_Fplus};
	modal_triad_addchord(g_named_chords, gensym("F+"), chord_Fplus, notes_per_scale);
	
	int chord_Fsplus[] = {Chord_Fsplus};
	modal_triad_addchord(g_named_chords, gensym("F#+"), chord_Fsplus, notes_per_scale);
	
	int chord_Gbplus[] = {Chord_Gbplus};
	modal_triad_addchord(g_named_chords, gensym("Gb+"), chord_Gbplus, notes_per_scale);
	
	int chord_Gplus[] = {Chord_Gplus};
	modal_triad_addchord(g_named_chords, gensym("G+"), chord_Gplus, notes_per_scale);
	
	int chord_Gsplus[] = {Chord_Gsplus};
	modal_triad_addchord(g_named_chords, gensym("G#+"), chord_Gsplus, notes_per_scale);
	
	int chord_Abplus[] = {Chord_Abplus};
	modal_triad_addchord(g_named_chords, gensym("Ab+"), chord_Abplus, notes_per_scale);
	
	int chord_Aplus[] = {Chord_Aplus};
	modal_triad_addchord(g_named_chords, gensym("A+"), chord_Aplus, notes_per_scale);
	
	int chord_Asplus[] = {Chord_Asplus};
	modal_triad_addchord(g_named_chords, gensym("A#+"), chord_Asplus, notes_per_scale);
	
	int chord_Bbplus[] = {Chord_Bbplus};
	modal_triad_addchord(g_named_chords, gensym("Bb+"), chord_Bbplus, notes_per_scale);
	
	int chord_Bplus[] = {Chord_Bplus};
	modal_triad_addchord(g_named_chords, gensym("B+"), chord_Bplus, notes_per_scale);
}


void modal_triad_register_diatonic_chords() {
	g_diatonic_chords = (t_hashtab *)hashtab_new(116);
	
	
	int chord1[] = {Chord1};
	modal_triad_addchord(g_diatonic_chords, gensym("1"), chord1, notes_per_scale*2);	
	
	int chord2[] = {Chord2};
	modal_triad_addchord(g_diatonic_chords, gensym("2"), chord2, notes_per_scale*2);	
	
	int chord3[] = {Chord3};
	modal_triad_addchord(g_diatonic_chords, gensym("3"), chord3, notes_per_scale*2);	
	
	int chord4[] = {Chord4};
	modal_triad_addchord(g_diatonic_chords, gensym("4"), chord4, notes_per_scale*2);	
	
	int chord5[] = {Chord5};
	modal_triad_addchord(g_diatonic_chords, gensym("5"), chord5, notes_per_scale*2);	
	
	int chord6[] = {Chord6};
	modal_triad_addchord(g_diatonic_chords, gensym("6"), chord6, notes_per_scale*2);	
	
	int chord7[] = {Chord7};
	modal_triad_addchord(g_diatonic_chords, gensym("7"), chord7, notes_per_scale*2);	
	
	int chord8[] = {Chord8};
	modal_triad_addchord(g_diatonic_chords, gensym("8"), chord8, notes_per_scale*2);	
	
	// Major 
	int chord_I[] = {Chord_I};
	modal_triad_addchord(g_diatonic_chords, gensym("I"), chord_I, notes_per_scale*2);	
	
	int chord_II[] = {Chord_II};
	modal_triad_addchord(g_diatonic_chords, gensym("II"), chord_II, notes_per_scale*2);	
	
	int chord_III[] = {Chord_III};
	modal_triad_addchord(g_diatonic_chords, gensym("III"), chord_III, notes_per_scale*2);	
	
	int chord_IV[] = {Chord_IV};
	modal_triad_addchord(g_diatonic_chords, gensym("IV"), chord_IV, notes_per_scale*2);	
	
	int chord_V[] = {Chord_V};
	modal_triad_addchord(g_diatonic_chords, gensym("V"), chord_V, notes_per_scale*2);	
	
	int chord_VI[] = {Chord_VI};
	modal_triad_addchord(g_diatonic_chords, gensym("VI"), chord_VI, notes_per_scale*2);	
	
	int chord_VII[] = {Chord_VII};
	modal_triad_addchord(g_diatonic_chords, gensym("VII"), chord_VII, notes_per_scale*2);	
	
	int chord_VIII[] = {Chord_VIII};
	modal_triad_addchord(g_diatonic_chords, gensym("VIII"), chord_VIII, notes_per_scale*2);	
	
	// Minor 
	int chord_i[] = {Chord_i};
	modal_triad_addchord(g_diatonic_chords, gensym("i"), chord_i, notes_per_scale*2);	
	
	int chord_ii[] = {Chord_ii};
	modal_triad_addchord(g_diatonic_chords, gensym("ii"), chord_ii, notes_per_scale*2);	
	
	int chord_iii[] = {Chord_iii};
	modal_triad_addchord(g_diatonic_chords, gensym("iii"), chord_iii, notes_per_scale*2);	
	
	int chord_iv[] = {Chord_iv};
	modal_triad_addchord(g_diatonic_chords, gensym("iv"), chord_iv, notes_per_scale*2);	
	
	int chord_v[] = {Chord_v};
	modal_triad_addchord(g_diatonic_chords, gensym("v"), chord_v, notes_per_scale*2);	
	
	int chord_vi[] = {Chord_vi};
	modal_triad_addchord(g_diatonic_chords, gensym("vi"), chord_vi, notes_per_scale*2);	
	
	int chord_vii[] = {Chord_vii};
	modal_triad_addchord(g_diatonic_chords, gensym("vii"), chord_vii, notes_per_scale*2);	
	
	int chord_viii[] = {Chord_viii};
	modal_triad_addchord(g_diatonic_chords, gensym("viii"), chord_viii, notes_per_scale*2);	
	
	// Augmented 
	int chord_Iplus[] = {Chord_Iplus};
	modal_triad_addchord(g_diatonic_chords, gensym("I+"), chord_Iplus, notes_per_scale*2);	
	
	int chord_IIplus[] = {Chord_IIplus};
	modal_triad_addchord(g_diatonic_chords, gensym("II+"), chord_IIplus, notes_per_scale*2);	
	
	int chord_IIIplus[] = {Chord_IIIplus};
	modal_triad_addchord(g_diatonic_chords, gensym("III+"), chord_IIIplus, notes_per_scale*2);	
	
	int chord_IVplus[] = {Chord_IVplus};
	modal_triad_addchord(g_diatonic_chords, gensym("IV+"), chord_IVplus, notes_per_scale*2);	
	
	int chord_Vplus[] = {Chord_Vplus};
	modal_triad_addchord(g_diatonic_chords, gensym("V+"), chord_Vplus, notes_per_scale*2);	
	
	int chord_VIplus[] = {Chord_VIplus};
	modal_triad_addchord(g_diatonic_chords, gensym("VI+"), chord_VIplus, notes_per_scale*2);	
	
	int chord_VIIplus[] = {Chord_VIIplus};
	modal_triad_addchord(g_diatonic_chords, gensym("VII+"), chord_VIIplus, notes_per_scale*2);	
	
	int chord_VIIIplus[] = {Chord_VIIIplus};
	modal_triad_addchord(g_diatonic_chords, gensym("VIII+"), chord_VIIIplus, notes_per_scale*2);	
	
	// Diminished 
	int chord_I0[] = {Chord_I0};
	modal_triad_addchord(g_diatonic_chords, gensym("I0"), chord_I0, notes_per_scale*2);	
	
	int chord_ii0[] = {Chord_ii0};
	modal_triad_addchord(g_diatonic_chords, gensym("ii0"), chord_ii0, notes_per_scale*2);	
	
	int chord_iii0[] = {Chord_iii0};
	modal_triad_addchord(g_diatonic_chords, gensym("iii0"), chord_iii0, notes_per_scale*2);	
	
	int chord_iv0[] = {Chord_iv0};
	modal_triad_addchord(g_diatonic_chords, gensym("iv0"), chord_iv0, notes_per_scale*2);	
	
	int chord_v0[] = {Chord_v0};
	modal_triad_addchord(g_diatonic_chords, gensym("v0"), chord_v0, notes_per_scale*2);	
	
	int chord_vi0[] = {Chord_vi0};
	modal_triad_addchord(g_diatonic_chords, gensym("vi0"), chord_vi0, notes_per_scale*2);	
	
	int chord_vii0[] = {Chord_vii0};
	modal_triad_addchord(g_diatonic_chords, gensym("vii0"), chord_vii0, notes_per_scale*2);	
	
	int chord_viii0[] = {Chord_viii0};
	modal_triad_addchord(g_diatonic_chords, gensym("viii0"), chord_viii0, notes_per_scale*2);	
	
	// V7 
	int chord_Vover1[] = {Chord_Vover1};
	modal_triad_addchord(g_diatonic_chords, gensym("V/1"), chord_Vover1, notes_per_scale*2);	
	
	int chord_Vover2[] = {Chord_Vover2};
	modal_triad_addchord(g_diatonic_chords, gensym("V/2"), chord_Vover2, notes_per_scale*2);	
	
	int chord_Vover3[] = {Chord_Vover3};
	modal_triad_addchord(g_diatonic_chords, gensym("V/3"), chord_Vover3, notes_per_scale*2);	
	
	int chord_Vover4[] = {Chord_Vover4};
	modal_triad_addchord(g_diatonic_chords, gensym("V/4"), chord_Vover4, notes_per_scale*2);	
	
	int chord_Vover5[] = {Chord_Vover5};
	modal_triad_addchord(g_diatonic_chords, gensym("V/5"), chord_Vover5, notes_per_scale*2);	
	
	int chord_Vover6[] = {Chord_Vover6};
	modal_triad_addchord(g_diatonic_chords, gensym("V/6"), chord_Vover6, notes_per_scale*2);	
	
	int chord_Vover7[] = {Chord_Vover7};
	modal_triad_addchord(g_diatonic_chords, gensym("V/7"), chord_Vover7, notes_per_scale*2);	
	
	int chord_Vover8[] = {Chord_Vover8};
	modal_triad_addchord(g_diatonic_chords, gensym("V/8"), chord_Vover8, notes_per_scale*2);	
	
	// vii 
	int chord_viiover1[] = {Chord_viiover1};
	modal_triad_addchord(g_diatonic_chords, gensym("vii/1"), chord_viiover1, notes_per_scale*2);	
	
	int chord_viiover2[] = {Chord_viiover2};
	modal_triad_addchord(g_diatonic_chords, gensym("vii/2"), chord_viiover2, notes_per_scale*2);	
	
	int chord_viiover3[] = {Chord_viiover3};
	modal_triad_addchord(g_diatonic_chords, gensym("vii/3"), chord_viiover3, notes_per_scale*2);	
	
	int chord_viiover4[] = {Chord_viiover4};
	modal_triad_addchord(g_diatonic_chords, gensym("vii/4"), chord_viiover4, notes_per_scale*2);	
	
	int chord_viiover5[] = {Chord_viiover5};
	modal_triad_addchord(g_diatonic_chords, gensym("vii/5"), chord_viiover5, notes_per_scale*2);	
	
	int chord_viiover6[] = {Chord_viiover6};
	modal_triad_addchord(g_diatonic_chords, gensym("vii/6"), chord_viiover6, notes_per_scale*2);	
	
	int chord_viiover7[] = {Chord_viiover7};
	modal_triad_addchord(g_diatonic_chords, gensym("vii/7"), chord_viiover7, notes_per_scale*2);	
	
	int chord_viiover8[] = {Chord_viiover8};
	modal_triad_addchord(g_diatonic_chords, gensym("vii/8"), chord_viiover8, notes_per_scale*2);	
	
	// vii0 
	int chord_vii0over1[] = {Chord_vii0over1};
	modal_triad_addchord(g_diatonic_chords, gensym("vii0/1"), chord_vii0over1, notes_per_scale*2);	
	
	int chord_vii0over2[] = {Chord_vii0over2};
	modal_triad_addchord(g_diatonic_chords, gensym("vii0/2"), chord_vii0over2, notes_per_scale*2);	
	
	int chord_vii0over3[] = {Chord_vii0over3};
	modal_triad_addchord(g_diatonic_chords, gensym("vii0/3"), chord_vii0over3, notes_per_scale*2);	
	
	int chord_vii0over4[] = {Chord_vii0over4};
	modal_triad_addchord(g_diatonic_chords, gensym("vii0/4"), chord_vii0over4, notes_per_scale*2);	
	
	int chord_vii0over5[] = {Chord_vii0over5};
	modal_triad_addchord(g_diatonic_chords, gensym("vii0/5"), chord_vii0over5, notes_per_scale*2);	
	
	int chord_vii0over6[] = {Chord_vii0over6};
	modal_triad_addchord(g_diatonic_chords, gensym("vii0/6"), chord_vii0over6, notes_per_scale*2);	
	
	int chord_vii0over7[] = {Chord_vii0over7};
	modal_triad_addchord(g_diatonic_chords, gensym("vii0/7"), chord_vii0over7, notes_per_scale*2);	
	
	int chord_vii0over8[] = {Chord_vii0over8};
	modal_triad_addchord(g_diatonic_chords, gensym("vii0/8"), chord_vii0over8, notes_per_scale*2);
		
	// iv 
	int chord_ivover1[] = {Chord_ivover1};
	modal_triad_addchord(g_diatonic_chords, gensym("iv/1"), chord_ivover1, notes_per_scale*2);	
	
	int chord_ivover2[] = {Chord_ivover2};
	modal_triad_addchord(g_diatonic_chords, gensym("iv/2"), chord_ivover2, notes_per_scale*2);	
	
	int chord_ivover3[] = {Chord_ivover3};
	modal_triad_addchord(g_diatonic_chords, gensym("iv/3"), chord_ivover3, notes_per_scale*2);	
	
	int chord_ivover4[] = {Chord_ivover4};
	modal_triad_addchord(g_diatonic_chords, gensym("iv/4"), chord_ivover4, notes_per_scale*2);	
	
	int chord_ivover5[] = {Chord_ivover5};
	modal_triad_addchord(g_diatonic_chords, gensym("iv/5"), chord_ivover5, notes_per_scale*2);	
	
	int chord_ivover6[] = {Chord_ivover6};
	modal_triad_addchord(g_diatonic_chords, gensym("iv/6"), chord_ivover6, notes_per_scale*2);	
	
	int chord_ivover7[] = {Chord_ivover7};
	modal_triad_addchord(g_diatonic_chords, gensym("iv/7"), chord_ivover7, notes_per_scale*2);	
	
	int chord_ivover8[] = {Chord_ivover8};
	modal_triad_addchord(g_diatonic_chords, gensym("iv/8"), chord_ivover8, notes_per_scale*2);	
	
	// Chromatic Root 
	int chord_7over2[] = {Chord_7over2};
	modal_triad_addchord(g_diatonic_chords, gensym("7/2"), chord_7over2, notes_per_scale*2);	
	
	int chord_7over3[] = {Chord_7over3};
	modal_triad_addchord(g_diatonic_chords, gensym("7/3"), chord_7over3, notes_per_scale*2);	
	
	int chord_7over4[] = {Chord_7over4};
	modal_triad_addchord(g_diatonic_chords, gensym("7/4"), chord_7over4, notes_per_scale*2);	
	
	int chord_7over5[] = {Chord_7over5};
	modal_triad_addchord(g_diatonic_chords, gensym("7/5"), chord_7over5, notes_per_scale*2);	
	
	int chord_7over6[] = {Chord_7over6};
	modal_triad_addchord(g_diatonic_chords, gensym("7/6"), chord_7over6, notes_per_scale*2);	
	
	int chord_7over7[] = {Chord_7over7};
	modal_triad_addchord(g_diatonic_chords, gensym("7/7"), chord_7over7, notes_per_scale*2);	
	
	int chord_7over1[] = {Chord_7over1};
	modal_triad_addchord(g_diatonic_chords, gensym("7/1"), chord_7over1, notes_per_scale*2);	
	
	int chord_7over8[] = {Chord_7over8};
	modal_triad_addchord(g_diatonic_chords, gensym("7/8"), chord_7over8, notes_per_scale*2);	
	
	
	// Neapolitan Sixth 
	int chord_N6[] = {Chord_N6};
	modal_triad_addchord(g_diatonic_chords, gensym("N6"), chord_N6, notes_per_scale*2);	
	
	int chord_N6over1[] = {Chord_N6over1};
	modal_triad_addchord(g_diatonic_chords, gensym("N6/1"), chord_N6over1, notes_per_scale*2);	
	
	int chord_N6over2[] = {Chord_N6over2};
	modal_triad_addchord(g_diatonic_chords, gensym("N6/2"), chord_N6over2, notes_per_scale*2);	
	
	int chord_N6over3[] = {Chord_N6over3};
	modal_triad_addchord(g_diatonic_chords, gensym("N6/3"), chord_N6over3, notes_per_scale*2);	
	
	int chord_N6over4[] = {Chord_N6over4};
	modal_triad_addchord(g_diatonic_chords, gensym("N6/4"), chord_N6over4, notes_per_scale*2);	
	
	int chord_N6over5[] = {Chord_N6over5};
	modal_triad_addchord(g_diatonic_chords, gensym("N6/5"), chord_N6over5, notes_per_scale*2);	
	
	int chord_N6over6[] = {Chord_N6over6};
	modal_triad_addchord(g_diatonic_chords, gensym("N6/6"), chord_N6over6, notes_per_scale*2);	
	
	int chord_N6over7[] = {Chord_N6over7};
	modal_triad_addchord(g_diatonic_chords, gensym("N6/7"), chord_N6over7, notes_per_scale*2);	
	
	int chord_N6over8[] = {Chord_N6over8};
	modal_triad_addchord(g_diatonic_chords, gensym("N6/8"), chord_N6over8, notes_per_scale*2);	
	
	
	// Italian Sixth 
	int chord_It6[] = {Chord_It6};
	modal_triad_addchord(g_diatonic_chords, gensym("It6"), chord_It6, notes_per_scale*2);	
	
	int chord_It6over1[] = {Chord_It6over1};
	modal_triad_addchord(g_diatonic_chords, gensym("It6/1"), chord_It6over1, notes_per_scale*2);	
	
	int chord_It6over2[] = {Chord_It6over2};
	modal_triad_addchord(g_diatonic_chords, gensym("It6/2"), chord_It6over2, notes_per_scale*2);	
	
	int chord_It6over3[] = {Chord_It6over3};
	modal_triad_addchord(g_diatonic_chords, gensym("It6/3"), chord_It6over3, notes_per_scale*2);	
	
	int chord_It6over4[] = {Chord_It6over4};
	modal_triad_addchord(g_diatonic_chords, gensym("It6/4"), chord_It6over4, notes_per_scale*2);	
	
	int chord_It6over5[] = {Chord_It6over5};
	modal_triad_addchord(g_diatonic_chords, gensym("It6/5"), chord_It6over5, notes_per_scale*2);	
	
	int chord_It6over6[] = {Chord_It6over6};
	modal_triad_addchord(g_diatonic_chords, gensym("It6/6"), chord_It6over6, notes_per_scale*2);	
	
	int chord_It6over7[] = {Chord_It6over7};
	modal_triad_addchord(g_diatonic_chords, gensym("It6/7"), chord_It6over7, notes_per_scale*2);	
	
	int chord_It6over8[] = {Chord_It6over8};
	modal_triad_addchord(g_diatonic_chords, gensym("It6/8"), chord_It6over8, notes_per_scale*2);	
	
	
	// German Sixth 
	int chord_Gr6[] = {Chord_Gr6};
	modal_triad_addchord(g_diatonic_chords, gensym("Gr6"), chord_Gr6, notes_per_scale*2);	
	
	int chord_Gr6over1[] = {Chord_Gr6over1};
	modal_triad_addchord(g_diatonic_chords, gensym("Gr6/1"), chord_Gr6over1, notes_per_scale*2);	
	
	int chord_Gr6over2[] = {Chord_Gr6over2};
	modal_triad_addchord(g_diatonic_chords, gensym("Gr6/2"), chord_Gr6over2, notes_per_scale*2);	
	
	int chord_Gr6over3[] = {Chord_Gr6over3};
	modal_triad_addchord(g_diatonic_chords, gensym("Gr6/3"), chord_Gr6over3, notes_per_scale*2);	
	
	int chord_Gr6over4[] = {Chord_Gr6over4};
	modal_triad_addchord(g_diatonic_chords, gensym("Gr6/4"), chord_Gr6over4, notes_per_scale*2);	
	
	int chord_Gr6over5[] = {Chord_Gr6over5};
	modal_triad_addchord(g_diatonic_chords, gensym("Gr6/5"), chord_Gr6over5, notes_per_scale*2);	
	
	int chord_Gr6over6[] = {Chord_Gr6over6};
	modal_triad_addchord(g_diatonic_chords, gensym("Gr6/6"), chord_Gr6over6, notes_per_scale*2);	
	
	int chord_Gr6over7[] = {Chord_Gr6over7};
	modal_triad_addchord(g_diatonic_chords, gensym("Gr6/7"), chord_Gr6over7, notes_per_scale*2);	
	
	int chord_Gr6over8[] = {Chord_Gr6over8};
	modal_triad_addchord(g_diatonic_chords, gensym("Gr6/8"), chord_Gr6over8, notes_per_scale*2);	
	
	// French, 0, Sixth, 0, 
	int chord_Fr6[] = {Chord_Fr6};
	modal_triad_addchord(g_diatonic_chords, gensym("Fr6"), chord_Fr6, notes_per_scale*2);	
	
	int chord_Fr6over1[] = {Chord_Fr6over1};
	modal_triad_addchord(g_diatonic_chords, gensym("Fr6/1"), chord_Fr6over1, notes_per_scale*2);	
	
	int chord_Fr6over2[] = {Chord_Fr6over2};
	modal_triad_addchord(g_diatonic_chords, gensym("Fr6/2"), chord_Fr6over2, notes_per_scale*2);	
	
	int chord_Fr6over3[] = {Chord_Fr6over3};
	modal_triad_addchord(g_diatonic_chords, gensym("Fr6/3"), chord_Fr6over3, notes_per_scale*2);	
	
	int chord_Fr6over4[] = {Chord_Fr6over4};
	modal_triad_addchord(g_diatonic_chords, gensym("Fr6/4"), chord_Fr6over4, notes_per_scale*2);	
	
	int chord_Fr6over5[] = {Chord_Fr6over5};
	modal_triad_addchord(g_diatonic_chords, gensym("Fr6/5"), chord_Fr6over5, notes_per_scale*2);	
	
	int chord_Fr6over6[] = {Chord_Fr6over6};
	modal_triad_addchord(g_diatonic_chords, gensym("Fr6/6"), chord_Fr6over6, notes_per_scale*2);	
	
	int chord_Fr6over7[] = {Chord_Fr6over7};
	modal_triad_addchord(g_diatonic_chords, gensym("Fr6/7"), chord_Fr6over7, notes_per_scale*2);	
	
	int chord_Fr6over8[] = {Chord_Fr6over8};
	modal_triad_addchord(g_diatonic_chords, gensym("Fr6/8"), chord_Fr6over8, notes_per_scale*2);		
}


