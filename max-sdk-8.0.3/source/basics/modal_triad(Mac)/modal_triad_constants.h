/*
 *  modal_triad_constants.h
 *  modal_triad
 *
 *  Copyright 2009 VJ Manzo. All rights reserved.
 *
 */


#define    num_inlets                10
#define    num_outlets                7
#define    num_pitches                56
#define notes_per_scale            7

// enumerated type for scale degrees, used as array index for pitches array
enum {
    deg1 = 0,
    deg2,
    deg3,
    deg4,
    deg5,
    deg6,
    deg7,
    deg8,
    
    deg9,
    deg10,
    deg11,
    deg12,
    deg13,
    deg14,
    deg15,
    
    deg16,
    deg17,
    deg18,
    deg19,
    deg20,
    deg21,
    deg22,
    
    deg23,
    deg24,
    deg25,
    deg26,
    deg27,
    deg28,
    deg29,
    
    deg30,
    deg31,
    deg32,
    deg33,
    deg34,
    deg35,
    deg36,
    
    chromatic1,
    chromatic2,
    chromatic3,
    chromatic4,
    chromatic5,
    chromatic6,
    chromatic7,
    
    chromatic8,
    chromatic9,
    chromatic10,
    chromatic11,
    chromatic12,
    chromatic13,
    chromatic14
};

#define array_length_named      7
#define array_length_diatonic (array_length_named*2)

// Diatonic Chord numbers
#define Chord1 deg1, 0, deg3, 0, deg5, 0, deg7, 0, deg9, 0, deg11, 0, deg13, 0
#define Chord2 deg2, 0, deg4, 0, deg6, 0, deg8, 0, deg10, 0, deg12, 0, deg14, 0
#define Chord3 deg3, 0, deg5, 0, deg7, 0, deg9, 0, deg11, 0, deg13, 0, deg15, 0
#define Chord4 deg4, 0, deg6, 0, deg8, 0, deg10, 0, deg12, 0, deg14, 0, deg16, 0
#define Chord5 deg5, 0, deg7, 0, deg9, 0, deg11, 0, deg13, 0, deg15, 0, deg17, 0
#define Chord6 deg6, 0, deg8, 0, deg10, 0, deg12, 0, deg14, 0, deg16, 0, deg18, 0
#define Chord7 deg7, 0, deg9, 0, deg11, 0, deg13, 0, deg15, 0, deg17, 0, deg19, 0
#define Chord8 deg8, 0, deg10, 0, deg12, 0, deg14, 0, deg16, 0, deg18, 0, deg20, 0

// Major Chord Roman Numeral classes
#define Chord_I        deg1, 0, deg1, 4, deg1, 7, deg7, 0, deg9, 0, deg11, 0, deg13, 0
#define Chord_II    deg2, 0, deg2, 4, deg2, 7, deg8, 0, deg10, 0, deg12, 0, deg14, 0
#define Chord_III    deg3, 0, deg3, 4, deg3, 7, deg9, 0, deg11, 0, deg13, 0, deg15, 0
#define Chord_IV    deg4, 0, deg4, 4, deg4, 7, deg10, 0, deg12, 0, deg14, 0, deg16, 0
#define Chord_V        deg5, 0, deg5, 4, deg5, 7, deg11, 0, deg13, 0, deg15, 0, deg17, 0
#define Chord_VI    deg6, 0, deg6, 4, deg6, 7, deg12, 0, deg14, 0, deg16, 0, deg18, 0
#define Chord_VII    deg7, 0, deg7, 4, deg7, 7, deg13, 0, deg15, 0, deg17, 0, deg19, 0
#define Chord_VIII    deg8, 0, deg8, 4, deg8, 7, deg14, 0, deg16, 0, deg18, 0, deg20, 0

// Minor Chord Roman Numeral classes
#define Chord_i        deg1, 0, deg1, 3, deg1, 7, deg7, 0, deg9, 0, deg11, 0, deg13, 0
#define Chord_ii    deg2, 0, deg2, 3, deg2, 7, deg8, 0, deg10, 0, deg12, 0, deg14, 0
#define Chord_iii    deg3, 0, deg3, 3, deg3, 7, deg9, 0, deg11, 0, deg13, 0, deg15, 0
#define Chord_iv    deg4, 0, deg4, 3, deg4, 7, deg10, 0, deg12, 0, deg14, 0, deg16, 0
#define Chord_v        deg5, 0, deg5, 3, deg5, 7, deg11, 0, deg13, 0, deg15, 0, deg17, 0
#define Chord_vi    deg6, 0, deg6, 3, deg6, 7, deg12, 0, deg14, 0, deg16, 0, deg18, 0
#define Chord_vii    deg7, 0, deg7, 3, deg7, 7, deg13, 0, deg15, 0, deg17, 0, deg19, 0
#define Chord_viii    deg8, 0, deg8, 3, deg8, 7, deg14, 0, deg16, 0, deg18, 0, deg20, 0

// Augmented Chord Roman Numeral classes
#define Chord_Iplus        deg1, 0, deg1, 4, deg1, 8, deg7, 0, deg9, 0, deg11, 0, deg13, 0
#define Chord_IIplus    deg2, 0, deg2, 4, deg2, 8, deg8, 0, deg10, 0, deg12, 0, deg14, 0
#define Chord_IIIplus    deg3, 0, deg3, 4, deg3, 8, deg9, 0, deg11, 0, deg13, 0, deg15, 0
#define Chord_IVplus    deg4, 0, deg4, 4, deg4, 8, deg10, 0, deg12, 0, deg14, 0, deg16, 0
#define Chord_Vplus        deg5, 0, deg5, 4, deg5, 8, deg11, 0, deg13, 0, deg15, 0, deg17, 0
#define Chord_VIplus    deg6, 0, deg6, 4, deg6, 8, deg12, 0, deg14, 0, deg16, 0, deg18, 0
#define Chord_VIIplus    deg7, 0, deg7, 4, deg7, 8, deg13, 0, deg15, 0, deg17, 0, deg19, 0
#define Chord_VIIIplus    deg8, 0, deg8, 4, deg8, 8, deg14, 0, deg16, 0, deg18, 0, deg20, 0

// Diminished Chord Roman Numeral classes
#define Chord_I0    deg1, 0, deg1, 3, deg1, 6, deg7, 0, deg9, 0, deg11, 0, deg13, 0
#define Chord_ii0    deg2, 0, deg2, 3, deg2, 6, deg8, 0, deg10, 0, deg12, 0, deg14, 0
#define Chord_iii0    deg3, 0, deg3, 3, deg3, 6, deg9, 0, deg11, 0, deg13, 0, deg15, 0
#define Chord_iv0    deg4, 0, deg4, 3, deg4, 6, deg10, 0, deg12, 0, deg14, 0, deg16, 0
#define Chord_v0    deg5, 0, deg5, 3, deg5, 6, deg11, 0, deg13, 0, deg15, 0, deg17, 0
#define Chord_vi0    deg6, 0, deg6, 3, deg6, 6, deg12, 0, deg14, 0, deg16, 0, deg18, 0
#define Chord_vii0    deg7, 0, deg7, 3, deg7, 6, deg13, 0, deg15, 0, deg17, 0, deg19, 0
#define Chord_viii0    deg8, 0, deg8, 3, deg8, 6, deg14, 0, deg16, 0, deg18, 0, deg20, 0

// V7 Chord Tonicizations
#define Chord_Vover1    deg1, 7, deg1, 11, deg1, 14, deg1, 17, deg13, 0, deg15, 0, deg17, 0
#define Chord_Vover2    deg2, 7, deg2, 11, deg2, 14, deg2, 17, deg14, 0, deg16, 0, deg18, 0
#define Chord_Vover3    deg3, 7, deg3, 11, deg3, 14, deg3, 17, deg15, 0, deg17, 0, deg19, 0
#define Chord_Vover4    deg4, 7, deg4, 11, deg4, 14, deg4, 17, deg16, 0, deg18, 0, deg20, 0
#define Chord_Vover5    deg5, 7, deg5, 11, deg5, 14, deg5, 17, deg17, 0, deg19, 0, deg21, 0
#define Chord_Vover6    deg6, 7, deg6, 11, deg6, 14, deg6, 17, deg18, 0, deg20, 0, deg22, 0
#define Chord_Vover7    deg7, 7, deg7, 11, deg7, 14, deg7, 17, deg19, 0, deg21, 0, deg23, 0
#define Chord_Vover8    deg8, 7, deg8, 11, deg8, 14, deg8, 17, deg20, 0, deg22, 0, deg24, 0

// vii Chord Tonicizations
#define Chord_viiover1    deg1, 11, deg1, 14, deg1, 17, deg1, 21, deg15, 0, deg17, 0, deg19, 0
#define Chord_viiover2    deg2, 11, deg2, 14, deg2, 17, deg2, 21, deg16, 0, deg18, 0, deg20, 0
#define Chord_viiover3    deg3, 11, deg3, 14, deg3, 17, deg3, 21, deg17, 0, deg19, 0, deg21, 0
#define Chord_viiover4    deg4, 11, deg4, 14, deg4, 17, deg4, 21, deg18, 0, deg20, 0, deg22, 0
#define Chord_viiover5    deg5, 11, deg5, 14, deg5, 17, deg5, 21, deg19, 0, deg21, 0, deg23, 0
#define Chord_viiover6    deg6, 11, deg6, 14, deg6, 17, deg6, 21, deg20, 0, deg22, 0, deg24, 0
#define Chord_viiover7    deg7, 11, deg7, 14, deg7, 17, deg7, 21, deg21, 0, deg23, 0, deg25, 0
#define Chord_viiover8    deg8, 11, deg8, 14, deg8, 17, deg8, 21, deg22, 0, deg24, 0, deg26, 0

// vii0 Chord Tonicizations
#define Chord_vii0over1    deg1, 11, deg1, 14, deg1, 17, deg1, 20, deg15, 0, deg17, 0, deg19, 0
#define Chord_vii0over2    deg2, 11, deg2, 14, deg2, 17, deg2, 20, deg16, 0, deg18, 0, deg20, 0
#define Chord_vii0over3    deg3, 11, deg3, 14, deg3, 17, deg3, 20, deg17, 0, deg19, 0, deg21, 0
#define Chord_vii0over4    deg4, 11, deg4, 14, deg4, 17, deg4, 20, deg18, 0, deg20, 0, deg22, 0
#define Chord_vii0over5    deg5, 11, deg5, 14, deg5, 17, deg5, 20, deg19, 0, deg21, 0, deg23, 0
#define Chord_vii0over6    deg6, 11, deg6, 14, deg6, 17, deg6, 20, deg20, 0, deg22, 0, deg24, 0
#define Chord_vii0over7    deg7, 11, deg7, 14, deg7, 17, deg7, 20, deg21, 0, deg23, 0, deg25, 0
#define Chord_vii0over8    deg8, 11, deg8, 14, deg8, 17, deg8, 20, deg22, 0, deg24, 0, deg26, 0

// iv Chord Tonicizations
#define Chord_ivover1    deg1, 5, deg1, 8, deg1, 12, deg10, 0, deg12, 0, deg14, 0, deg16, 0
#define Chord_ivover2    deg2, 5, deg2, 8, deg2, 12, deg11, 0, deg13, 0, deg15, 0, deg17, 0
#define Chord_ivover3    deg3, 5, deg3, 8, deg3, 12, deg12, 0, deg14, 0, deg16, 0, deg18, 0
#define Chord_ivover4    deg4, 5, deg4, 8, deg4, 12, deg13, 0, deg15, 0, deg17, 0, deg19, 0
#define Chord_ivover5    deg5, 5, deg5, 8, deg5, 12, deg14, 0, deg16, 0, deg18, 0, deg20, 0
#define Chord_ivover6    deg6, 5, deg6, 8, deg6, 12, deg15, 0, deg17, 0, deg19, 0, deg21, 0
#define Chord_ivover7    deg7, 5, deg7, 8, deg7, 12, deg16, 0, deg18, 0, deg20, 0, deg22, 0
#define Chord_ivover8    deg8, 5, deg8, 8, deg8, 12, deg17, 0, deg19, 0, deg21, 0, deg23, 0

// Chromatic Root Chord Tonicizations
#define Chord_7over2    chromatic1, 0, deg3, 0, deg5, 0, deg7, 0, deg9, 0, deg11, 0, deg13, 0
#define Chord_7over3    chromatic2, 0, deg4, 0, deg6, 0, deg8, 0, deg10, 0, deg12, 0, deg14, 0
#define Chord_7over4    chromatic3, 0, deg5, 0, deg7, 0, deg9, 0, deg11, 0, deg13, 0, deg15, 0
#define Chord_7over5    chromatic4, 0, deg6, 0, deg8, 0, deg10, 0, deg12, 0, deg14, 0, deg16, 0
#define Chord_7over6    chromatic5, 0, deg7, 0, deg9, 0, deg11, 0, deg13, 0, deg15, 0, deg17, 0
#define Chord_7over7    chromatic6, 0, deg8, 0, deg10, 0, deg12, 0, deg14, 0, deg16, 0, deg18, 0
#define Chord_7over1    chromatic7, 0, deg9, 0, deg11, 0, deg13, 0, deg15, 0, deg17, 0, deg19, 0
#define Chord_7over8    chromatic7, 0, deg9, 0, deg11, 0, deg13, 0, deg15, 0, deg17, 0, deg19, 0


// Neapolitan Sixth Chord + Tonicizations
#define Chord_N6        deg1, 1, deg1, 5, deg1, 8, deg8, 0, deg10, 0, deg12, 0, deg14, 0
#define Chord_N6over1    deg1, 1, deg1, 5, deg1, 8, deg8, 0, deg10, 0, deg12, 0, deg14, 0
#define Chord_N6over2    deg2, 1, deg2, 5, deg2, 8, deg9, 0, deg11, 0, deg13, 0, deg15, 0
#define Chord_N6over3    deg3, 1, deg3, 5, deg3, 8, deg10, 0, deg12, 0, deg14, 0, deg16, 0
#define Chord_N6over4    deg4, 1, deg4, 5, deg4, 8, deg11, 0, deg13, 0, deg15, 0, deg17, 0
#define Chord_N6over5    deg5, 1, deg5, 5, deg5, 8, deg12, 0, deg14, 0, deg16, 0, deg18, 0
#define Chord_N6over6    deg6, 1, deg6, 5, deg6, 8, deg13, 0, deg15, 0, deg17, 0, deg19, 0
#define Chord_N6over7    deg7, 1, deg7, 5, deg7, 8, deg14, 0, deg16, 0, deg18, 0, deg20, 0
#define Chord_N6over8    deg8, 1, deg8, 5, deg8, 8, deg15, 0, deg17, 0, deg19, 0, deg21, 0


// Italian Sixth Chord + Tonicizations
#define Chord_It6        deg1, 8, deg1, 12, deg1, 18, deg12, 0, deg14, 0, deg16, 0, deg18, 0
#define Chord_It6over1    deg1, 8, deg1, 12, deg1, 18, deg12, 0, deg14, 0, deg16, 0, deg18, 0
#define Chord_It6over2    deg2, 8, deg2, 12, deg2, 18, deg13, 0, deg15, 0, deg17, 0, deg19, 0
#define Chord_It6over3    deg3, 8, deg3, 12, deg3, 18, deg14, 0, deg16, 0, deg18, 0, deg20, 0
#define Chord_It6over4    deg4, 8, deg4, 12, deg4, 18, deg15, 0, deg17, 0, deg19, 0, deg21, 0
#define Chord_It6over5    deg5, 8, deg5, 12, deg5, 18, deg16, 0, deg18, 0, deg20, 0, deg22, 0
#define Chord_It6over6    deg6, 8, deg6, 12, deg6, 18, deg17, 0, deg19, 0, deg21, 0, deg23, 0
#define Chord_It6over7    deg7, 8, deg7, 12, deg7, 18, deg18, 0, deg20, 0, deg22, 0, deg24, 0
#define Chord_It6over8    deg8, 8, deg8, 12, deg8, 18, deg19, 0, deg21, 0, deg23, 0, deg25, 0


// German Sixth Chord_s + Tonicizations
#define Chord_Gr6        deg1, 8, deg1, 12, deg1, 15, deg1, 18, deg14, 0, deg16, 0, deg18, 0
#define Chord_Gr6over1    deg1, 8, deg1, 12, deg1, 15, deg1, 18, deg14, 0, deg16, 0, deg18, 0
#define Chord_Gr6over2    deg2, 8, deg2, 12, deg2, 15, deg2, 18, deg15, 0, deg17, 0, deg19, 0
#define Chord_Gr6over3    deg3, 8, deg3, 12, deg3, 15, deg3, 18, deg16, 0, deg18, 0, deg20, 0
#define Chord_Gr6over4    deg4, 8, deg4, 12, deg4, 15, deg4, 18, deg17, 0, deg19, 0, deg21, 0
#define Chord_Gr6over5    deg5, 8, deg5, 12, deg5, 15, deg5, 18, deg18, 0, deg20, 0, deg22, 0
#define Chord_Gr6over6    deg6, 8, deg6, 12, deg6, 15, deg6, 18, deg19, 0, deg21, 0, deg23, 0
#define Chord_Gr6over7    deg7, 8, deg7, 12, deg7, 15, deg7, 18, deg20, 0, deg22, 0, deg24, 0
#define Chord_Gr6over8    deg8, 8, deg8, 12, deg8, 15, deg8, 18, deg21, 0, deg23, 0, deg25, 0

// French, 0, Sixth, 0, Chord_s, 0, +, 0, Tonicizations
#define Chord_Fr6        deg1, 8, deg1, 12, deg1, 14, deg1, 18, deg14, 0, deg16, 0, deg18, 0
#define Chord_Fr6over1    deg1, 8, deg1, 12, deg1, 14, deg1, 18, deg14, 0, deg16, 0, deg18, 0
#define Chord_Fr6over2    deg2, 8, deg2, 12, deg2, 14, deg2, 18, deg15, 0, deg17, 0, deg19, 0
#define Chord_Fr6over3    deg3, 8, deg3, 12, deg3, 14, deg3, 18, deg16, 0, deg18, 0, deg20, 0
#define Chord_Fr6over4    deg4, 8, deg4, 12, deg4, 14, deg4, 18, deg17, 0, deg19, 0, deg21, 0
#define Chord_Fr6over5    deg5, 8, deg5, 12, deg5, 14, deg5, 18, deg18, 0, deg20, 0, deg22, 0
#define Chord_Fr6over6    deg6, 8, deg6, 12, deg6, 14, deg6, 18, deg19, 0, deg21, 0, deg23, 0
#define Chord_Fr6over7    deg7, 8, deg7, 12, deg7, 14, deg7, 18, deg20, 0, deg22, 0, deg24, 0
#define Chord_Fr6over8    deg8, 8, deg8, 12, deg8, 14, deg8, 18, deg21, 0, deg23, 0, deg25, 0

// "Named" chords

// Major Letter Name Chord
#define Chord_C        0, 4, 7, 11, 14, 17, 21
#define Chord_Cs    1, 5, 8, 12, 15, 18, 22
#define Chord_Db    1, 5, 8, 12, 15, 18, 22
#define Chord_D        2, 6, 9, 13, 16, 19, 23
#define Chord_Ds    3, 7, 10, 14, 17, 20, 24
#define Chord_Eb    3, 7, 10, 14, 17, 20, 24
#define Chord_E        4, 8, 11, 15, 18, 21, 25
#define Chord_F        5, 9, 12, 16, 19, 22, 26
#define Chord_Fs    6, 10, 13, 17, 20, 23, 27
#define Chord_Gb    6, 10, 13, 17, 20, 23, 27
#define Chord_G        7, 11, 14, 18, 21, 24, 28
#define Chord_Gs    8, 12, 15, 19, 22, 25, 29
#define Chord_Ab    8, 12, 15, 19, 22, 25, 29
#define Chord_A        9, 13, 16, 20, 23, 26, 30
#define Chord_As    10, 14, 17, 21, 24, 27, 31
#define Chord_Bb    10, 14, 17, 21, 24, 27, 31
#define Chord_B        11, 15, 18, 22, 25, 28, 32

//Minor Letter Name Chord
#define Chord_c        0, 3, 7, 10, 14, 17, 20
#define Chord_cs    1, 4, 8, 11, 15, 18, 21
#define Chord_db    1, 4, 8, 11, 15, 18, 21
#define Chord_d        2, 5, 9, 12, 16, 19, 22
#define Chord_ds    3, 6, 10, 13, 17, 20, 23
#define Chord_eb    3, 6, 10, 13, 17, 20, 23
#define Chord_e        4, 7, 11, 14, 18, 21, 24
#define Chord_f        5, 8, 12, 15, 19, 22, 25
#define Chord_fs    6, 9, 13, 16, 20, 23, 26
#define Chord_gb    6, 9, 13, 16, 20, 23, 26
#define Chord_g        7, 10, 14, 17, 21, 24, 27
#define Chord_gs    8, 11, 15, 18, 22, 25, 28
#define Chord_ab    8, 11, 15, 18, 22, 25, 28
#define Chord_a        9, 12, 16, 19, 23, 26, 29
#define Chord_as    10, 13, 17, 20, 24, 27, 30
#define Chord_bb    10, 13, 17, 20, 24, 27, 30
#define Chord_b        11, 14, 18, 21, 25, 28, 31

//Diminished Letter Name Chord
#define Chord_c0    0, 3, 6, 10, 13, 17, 20
#define Chord_cs0    1, 4, 7, 11, 14, 18, 21
#define Chord_db0    1, 4, 7, 11, 14, 18, 21
#define Chord_d0    2, 5, 8, 12, 15, 19, 22
#define Chord_ds0    3, 6, 9, 13, 16, 20, 23
#define Chord_eb0    3, 6, 9, 13, 16, 20, 23
#define Chord_e0    4, 7, 10, 14, 17, 21, 24
#define Chord_f0    5, 8, 11, 15, 18, 22, 25
#define Chord_fs0    6, 9, 12, 16, 19, 23, 26
#define Chord_gb0    6, 9, 12, 16, 19, 23, 26
#define Chord_g0    7, 10, 13, 17, 20, 24, 27
#define Chord_gs0    8, 11, 14, 18, 21, 25, 28
#define Chord_ab0    8, 11, 14, 18, 21, 25, 28
#define Chord_a0    9, 12, 15, 19, 22, 26, 29
#define Chord_as0    10, 13, 16, 20, 23, 27, 30
#define Chord_bb0    10, 13, 16, 20, 23, 27, 30
#define Chord_b0    11, 14, 17, 21, 24, 28, 31

// Augmented Letter Name Chord
#define Chord_Cplus        0, 4, 8, 11, 14, 17, 21
#define Chord_Csplus    1, 5, 9, 12, 15, 18, 22
#define Chord_Dbplus    1, 5, 9, 12, 15, 18, 22
#define Chord_Dplus        2, 6, 10, 13, 16, 19, 23
#define Chord_Dsplus    3, 7, 11, 14, 17, 20, 24
#define Chord_Ebplus    3, 7, 11, 14, 17, 20, 24
#define Chord_Eplus        4, 8, 12, 15, 18, 21, 25
#define Chord_Fplus        5, 9, 13, 16, 19, 22, 26
#define Chord_Fsplus    6, 10, 14, 17, 20, 23, 27
#define Chord_Gbplus    6, 10, 14, 17, 20, 23, 27
#define Chord_Gplus        7, 11, 15, 18, 21, 24, 28
#define Chord_Gsplus    8, 12, 16, 19, 22, 25, 29
#define Chord_Abplus    8, 12, 16, 19, 22, 25, 29
#define Chord_Aplus        9, 13, 17, 20, 23, 26, 30
#define Chord_Asplus    10, 14, 18, 21, 24, 27, 31
#define Chord_Bbplus    10, 14, 18, 21, 24, 27, 31
#define Chord_Bplus        11, 15, 19, 22, 25, 28, 32
