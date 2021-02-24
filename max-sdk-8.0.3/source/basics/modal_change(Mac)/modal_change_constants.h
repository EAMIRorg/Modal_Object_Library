/*
 *  modal_change_constants.h
 *  modal_change
 *
 *  Created by Jonathan Bailey on 5/10/09, jonb@drumwell.net.
 *  Copyright 2009 VJ Manzo. All rights reserved.
 *
 */

// note values - pitch class
enum {
	kNoteValueC,
	kNoteValueCs,
	kNoteValueD,
	kNoteValueDs,
	kNoteValueE,
	kNoteValueF,
	kNoteValueFs,
	kNoteValueG,
	kNoteValueGs,
	kNoteValueA,
	kNoteValueAs,	
	kNoteValueB
};

// mode values
enum {
	kModeValueIonian,
	kModeValueDorian,
	kModeValuePhrygian,
	kModeValueLydian,
	kModeValueMixolydian,
	kModeValueAeolian,
	kModeValueLocrian,
	kModeValueHarmonic_major,
	kModeValueDorian_b5,
	kModeValuePhrygian_b4,
	kModeValueLydian_b3,
	kModeValueMixolydian_b2,
	kModeValueAeolian_b1,
	kModeValueLocrian_b7,
	kModeValueHarmonic_minor,
	kModeValueLocrian_s6,
	kModeValueIonian_s5,
	kModeValueDorian_s4,
	kModeValuePhrygian_s3,
	kModeValueLydian_s2,
	kModeValueMixolydian_s1,
	kModeValueMelodic_minor,
	kModeValueDorian_b2,
	kModeValueLydian_s5,
	kModeValueLydian_b7,
	kModeValueMixolydian_b6,
	kModeValueLocrian_s2,
	kModeValueLocrian_b4,
    kModeValuePentatonic_1,
    kModeValuePentatonic_2,
    kModeValuePentatonic_3,
    kModeValuePentatonic_4,
    kModeValuePentatonic_5,
};

// note name constants
#define name_C				"c"
#define name_Cs				"c#"
#define name_Db				"db"
#define name_D				"d"
#define name_Ds				"d#"
#define name_Eb				"eb"
#define name_E				"e"
#define name_F				"f"
#define name_Fs				"f#"
#define name_Gb				"gb"
#define name_G				"g"
#define name_Gs				"g#"
#define name_Ab				"ab"
#define name_A				"a"
#define name_As				"a#"
#define name_Bb				"bb"
#define name_B				"b"

// mode name constants
#define name_major				"major"
#define name_minor				"minor"
#define name_ionian				"ionian"
#define name_dorian				"dorian"
#define name_phrygian			"phrygian"
#define name_lydian				"lydian"
#define name_mixolydian			"mixolydian"
#define name_aeolian			"aeolian"
#define name_locrian			"locrian"
#define name_harmonic_major		"harmonic_major"
#define name_dorian_b5			"dorian_b5"
#define name_phrygian_b4		"phrygian_b4"
#define name_lydian_b3			"lydian_b3"
#define name_mixolydian_b2		"mixolydian_b2"
#define name_aeolian_b1			"aeolian_b1"
#define name_locrian_b7			"locrian_b7"
#define name_harmonic_minor		"harmonic_minor"
#define name_locrian_s6			"locrian_#6"
#define name_ionian_s5			"ionian_#5"
#define name_dorian_s4			"dorian_#4"
#define name_phrygian_s3		"phrygian_#3"
#define name_lydian_s2			"lydian_#2"
#define name_mixolydian_s1		"mixolydian_#1"
#define name_melodic_minor		"melodic_minor"
#define name_dorian_b2			"dorian_b2"
#define name_lydian_s5			"lydian_#5"
#define name_lydian_b7			"lydian_b7"
#define name_mixolydian_b6		"mixolydian_b6"
#define name_locrian_s2			"locrian_#2"
#define name_locrian_b4			"locrian_b4"
#define name_pentatonic_1       "pentatonic_1"
#define name_pentatonic_2       "pentatonic_2"
#define name_pentatonic_3       "pentatonic_3"
#define name_pentatonic_4       "pentatonic_4"
#define name_pentatonic_5       "pentatonic_5"

// mode value constants
#define scale_ionian			2, 2, 1, 2, 2, 2, 1 
#define scale_dorian			2, 1, 2, 2, 2, 1, 2
#define scale_phrygian			1, 2, 2, 2, 1, 2, 2
#define scale_lydian			2, 2, 2, 1, 2, 2, 1
#define scale_mixolydian		2, 2, 1, 2, 2, 1, 2
#define scale_aeolian			2, 1, 2, 2, 1, 2, 2 
#define scale_locrian			1, 2, 2, 1, 2, 2, 2 
#define scale_harmonic_major	2, 2, 1, 2, 1, 3, 1 
#define scale_dorian_b5			2, 1, 2, 1, 3, 1, 2		
#define scale_phrygian_b4		1, 2, 1, 3, 1, 2, 2 
#define scale_lydian_b3			2, 1, 3, 1, 2, 2, 1 
#define scale_mixolydian_b2		1, 3, 1, 2, 2, 1, 2 
#define scale_aeolian_b1		3, 1, 2, 2, 1, 2, 1 
#define scale_locrian_b7		1, 2, 2, 1, 2, 1, 3 
#define scale_harmonic_minor	2, 1, 2, 2, 1, 3, 1 
#define scale_locrian_s6		1, 2, 2, 1, 3, 1, 2 
#define scale_ionian_s5			2, 2, 1, 3, 1, 2, 1 
#define scale_dorian_s4			2, 1, 3, 1, 2, 1, 2 
#define scale_phrygian_s3		1, 3, 1, 2, 1, 2, 2
#define scale_lydian_s2			3, 1, 2, 1, 2, 2, 1
#define scale_mixolydian_s1		1, 2, 1, 2, 2, 1, 3 
#define scale_melodic_minor		2, 1, 2, 2, 2, 2, 1
#define scale_dorian_b2			1, 2, 2, 2, 2, 1, 2
#define scale_lydian_s5			2, 2, 2, 2, 1, 2, 1
#define scale_lydian_b7			2, 2, 2, 1, 2, 1, 2 
#define scale_mixolydian_b6		2, 2, 1, 2, 1, 2, 2
#define scale_locrian_s2		2, 1, 2, 1, 2, 2, 2
#define scale_locrian_b4		1, 2, 1, 2, 2, 2, 2
#define scale_pentatonic_1      2, 2, 3, 2, 3, 2, 2
#define scale_pentatonic_2      2, 3, 2, 3, 2, 2, 3
#define scale_pentatonic_3      3, 2, 3, 2, 2, 3, 2
#define scale_pentatonic_4      2, 3, 2, 2, 3, 2, 3
#define scale_pentatonic_5      3, 2, 2, 3, 2, 3, 2



// mode groupings
#define major_modes				name_ionian, name_dorian, name_phrygian, name_lydian, name_mixolydian, name_aeolian, name_locrian
#define harmonic_major_modes	name_harmonic_major, name_dorian_b5, name_phrygian_b4, name_lydian_b3, name_mixolydian_b2, name_aeolian_b1, name_locrian_b7
#define harmonic_minor_modes	name_harmonic_minor, name_locrian_s6, name_ionian_s5, name_dorian_s4, name_phrygian_s3, name_lydian_s2, name_mixolydian_s1
#define melodic_minor_modes		name_melodic_minor, name_dorian_b2, name_lydian_s5, name_lydian_b7, name_mixolydian_b6, name_locrian_s2, name_locrian_b4
#define pentatonic_modes		name_pentatonic_1, name_pentatonic_2, name_pentatonic_3, name_pentatonic_4, name_pentatonic_5

// mode text
#define text_major_modes			"mode %d of the major scale"
#define text_harmonic_major_modes	"mode %d of the harmonic major scale"
#define text_melodic_minor_modes	"mode %d of the melodic minor scale"
#define text_harmonic_minor_modes	"mode %d of the harmonic minor scale"
#define text_pentatonic_modes       "mode %d of the pentatonic scale"




// some misc UI view constants
#define box_height_total		(46.+21.)
#define box_width_total			(134.+547.)
#define box_height_root			(46./box_height_total)
#define box_width_root			(134./box_width_total)
#define box_height_mode			(46./box_height_total)
#define box_width_mode			(547./box_width_total)
#define box_height_intervals	(21./box_height_total)
#define box_width_intervals		(254./box_width_total)
#define box_height_desc			(21./box_height_total)
#define box_width_desc			(426./box_width_total)

#define box_corner_radius		8.

#define box_color1_r			.76
#define box_color1_g			.71
#define box_color1_b			.81
#define box_color1_a			1.0

#define box_color2_mult			.8

#define box_color2_r			(box_color1_r*box_color2_mult)
#define box_color2_g			(box_color1_g*box_color2_mult)
#define box_color2_b			(box_color1_b*box_color2_mult)
#define box_color2_a			1.0

#define font_face				"Arial"
#define font_size_small			14
#define font_size_large			36

#define font_color_r			0.
#define font_color_g			0.
#define font_color_b			0.
#define font_color_a			1.

#define text_offset_x			(6/box_width_total)
#define text_offset_y			(-4/box_height_total)

#define	num_outlets				9

#define default_string			"====="
