/*
 *------------------------------------------------------------------------
 * FeynDiagram
 *    This file is part of the FeynDiagram C++ library for creation
 *    of Feynman diagrams.
 *
 * Version $Revision: 2.5 $,  $Date: 2000/04/18 17:03:05 $
 *
 * by Bill Dimm,  bdimm@hotneuron.com
 *
 * Copyright 1993 Bill Dimm
 *    This code may be freely distributed.  No fee beyond a reasonable
 *    copying fee may be charged for this software.
 *    This code may not be included in commercial software without the
 *    author's permission.  If you modify this code and decide to
 *    distribute it, you MUST make it clear that it is a modified version.
 *------------------------------------------------------------------------
 */

#include <FeynmanDiagram/text2PS.h>
#include <ctype.h>
#include <string.h>
#ifdef NOOSFCN
	extern "C" { void exit(int); }
#else
//#  include <osfcn.h>
#endif

using namespace std;

static char sccsid_text2PS[] = "$Id: text2PS.C,v 2.5 2000/04/18 17:03:05 billd Exp $";

#define ERRSTR "   ** "

/*
 * text2PS() will convert a "TeX-like" string of text to postscript.
 * Note that text2PS() is a stand-alone function (ie. just need this file
 * and text2PS.h).  Note that text2PS assumes that a PostScript "max"
 * macro has been defined in the (user provided) prologue.  It also 
 * requires a "SF" macro, which acts like selectfont.
 * SUGGESTED POSTSCRIPT PROLOG:
 *
 *     /max { 2 copy lt {exch} if pop } def
 *
 *     /SF* {  exch findfont exch scalefont setfont } bind def
 *     
 *     systemdict /selectfont known
 *       { /SF /selectfont load def }
 *       { /SF /SF* load def }
 *       ifelse
 *
 *      /CF /currentflat load def
 *      /CP /charpath load def
 *      /CPT /currentpoint load def
 *      /FP /flattenpath load def
 *      /L2 /lineto load def
 *      /M2 /moveto load def
 *      /NP /newpath load def
 *      /PBX /pathbbox load def
 *      /RM2 /rmoveto load def
 *      /S /show load def
 *      /SLW /setlinewidth load def
 *      /ST /stroke load def
 */

/* WARNING: \overline is not really done properly.  See note below.
 */

/* FONTSHRINK is the amount to shrink the font by when doing superscripts
 * or subscripts.
 */
#define FONTSHRINK 0.7

// SYMBOLFONT is the name of the Postscript symbol font
#define SYMBOLFONT (char *)"Symbol"

/* PRIMESCALE is the amount to scale the Symbol font's prime by to
 * make it into a full size character (instead of a superscript)
 */
#define PRIMESCALE 1.7

/* OVERLINE_SHIFT is the fraction of the current font size to shift
 * up before doing the overline
 */
#define OVERLINE_SHIFT 0.15

/* OVERLINE_THICKNESS is the fraction of the current font size to
 * make the thickness of the overline
 */
#define OVERLINE_THICKNESS 0.07

/* TILDE_HEIGHT is fraction of the current font size to make the tilde */
#define TILDE_HEIGHT .12

/* ARROW_LENGTH is length of arrow as frac of current font size */
#define ARROW_LENGTH .18
#define ARROW_ANGLE 22


struct text2PS_symbol_translation
	{
	char *insym;
	char *outsym;
	};


static struct text2PS_symbol_translation text2PS_syms[] = 
	{
		{ (char *)"alpha"      , (char *)"\\141" },
		{ (char *)"beta"       , (char *)"\\142" },
		{ (char *)"gamma"      , (char *)"\\147" },
		{ (char *)"delta"      , (char *)"\\144" },
		{ (char *)"varepsilon" , (char *)"\\145" },
		{ (char *)"zeta"       , (char *)"\\172" },
		{ (char *)"eta"        , (char *)"\\150" },
		{ (char *)"theta"      , (char *)"\\161" },
		{ (char *)"vartheta"   , (char *)"\\112" },
		{ (char *)"iota"       , (char *)"\\151" },
		{ (char *)"kappa"      , (char *)"\\153" },
		{ (char *)"lambda"     , (char *)"\\154" },
		{ (char *)"mu"         , (char *)"\\155" },
		{ (char *)"nu"         , (char *)"\\156" },
		{ (char *)"xi"         , (char *)"\\170" },
		{ (char *)"pi"         , (char *)"\\160" },
		{ (char *)"rho"        , (char *)"\\162" },
		{ (char *)"sigma"      , (char *)"\\163" },
		{ (char *)"varsigma"   , (char *)"\\126" },
		{ (char *)"tau"        , (char *)"\\164" },
		{ (char *)"upsilon"    , (char *)"\\165" },
		{ (char *)"phi"        , (char *)"\\146" },
		{ (char *)"varphi"     , (char *)"\\152" },
		{ (char *)"chi"        , (char *)"\\143" },
		{ (char *)"psi"        , (char *)"\\171" },
		{ (char *)"omega"      , (char *)"\\167" },
		{ (char *)"Gamma"      , (char *)"\\107" },
		{ (char *)"Delta"      , (char *)"\\104" },
		{ (char *)"Theta"      , (char *)"\\121" },
		{ (char *)"Lambda"     , (char *)"\\114" },
		{ (char *)"Xi"         , (char *)"\\130" },
		{ (char *)"Pi"         , (char *)"\\120" },
		{ (char *)"Sigma"      , (char *)"\\123" },
		{ (char *)"Upsilon"    , (char *)"\\241" },
		{ (char *)"Phi"        , (char *)"\\106" },
		{ (char *)"Psi"        , (char *)"\\131" },
		{ (char *)"Omega"      , (char *)"\\127" },
		{ (char *)"Re"         , (char *)"\\302" },
		{ (char *)"Im"         , (char *)"\\301" },
		{ (char *)"partial"    , (char *)"\\266" },
		{ (char *)"infty"      , (char *)"\\245" },
		{ (char *)"nabla"      , (char *)"\\321" },
		{ (char *)"equiv"      , (char *)"\\272" },
		{ (char *)"sim"        , (char *)"\\176" },
		{ (char *)"approx"     , (char *)"\\273" },
		{ (char *)"conj"       , (char *)"\\100" },
		{ (char *)"propto"     , (char *)"\\265" },
		{ (char *)"perp"       , (char *)"\\136" },
		{ (char *)"cdot"       , (char *)"\\327" },
		{ (char *)"times"      , (char *)"\\264" },
		{ (char *)"ast"        , (char *)"\\052" },
		{ (char *)"bullet"     , (char *)"\\267" },
		{ (char *)"dag"        , (char *)"SPECIAL" },
		{ (char *)"leftarrow"  , (char *)"\\254" },
		{ (char *)"Leftarrow"  , (char *)"\\334" },
		{ (char *)"rightarrow" , (char *)"\\256" },
		{ (char *)"Rightarrow" , (char *)"\\336" },
		{ (char *)"leftrightarrow" , (char *)"\\253" },
		{ (char *)"Leftrightarrow" , (char *)"\\333" },
		{ (char *)"uparrow"    , (char *)"\\255" },
		{ (char *)"Uparrow"    , (char *)"\\335" },
		{ (char *)"downarrow"  , (char *)"\\257" },
		{ (char *)"Downarrow"  , (char *)"\\337" },
		{ (char *)"langle"     , (char *)"\\341" },
		{ (char *)"rangle"     , (char *)"\\361" },
		{ (char *)"vert"       , (char *)"\\174" },
		{ (char *)"copyright"  , (char *)"\\323" },
		{ (char *)"prime"      , (char *)"\\264"},
                { (char *)"plus"       , (char *)"\\053"},
		{ (char *)"minus"      , (char *)"\\055"},
		{ (char *)"overline"   , (char *)"SPECIAL"},
		{ (char *)"overrightarrow"   , (char *)"SPECIAL"},
		{ (char *)"widetilde"      , (char *)"SPECIAL"},
		{ (char *)"tildebar"      , (char *)"SPECIAL"},
                { (char *)"pm"         , (char *)"\\261"}
	};


static void startfont(ostream &out, char *fontname, double fontsize)
	{
	out << "/" << fontname << " " << fontsize << " SF\n";
	out << "(";
	}


/* If pathonly is true, it just finds the path path for the text rather
 * than actually filling it (using show)
 */
static void endfont(ostream &out, int pathonly)
	{
	if (pathonly)
		out << ") true CP\n";
	else
		out << ") S\n";
	}


static char *outputobj(ostream &out, char *textptr, char *fontname, double fontsize, int pathonly);


/* When this exits, there is no font active, and assumes there is no
 * font active when it starts.
 */
static char *outputsubscript(ostream &out, char *textptr, char *fontname, double fontsize, int pathonly)
	{
	char *result;

	out << "0 " << fontsize / 2 - fontsize * FONTSHRINK << " RM2\n";
	startfont(out,fontname,fontsize * FONTSHRINK);
	result = outputobj(out,textptr,fontname,fontsize * FONTSHRINK,pathonly);
	endfont(out,pathonly);
	return result;
	}


/* When this exits, there is no font active, and assumes there is no
 * font active when it starts.
 */
static char *outputsuperscript(ostream &out, char *textptr, char *fontname, double fontsize, int pathonly)
	{
	char *result;

	out << "0 " << fontsize / 2 << " RM2\n";
	startfont(out,fontname,fontsize * FONTSHRINK);
	result = outputobj(out,textptr,fontname,fontsize * FONTSHRINK,pathonly);
	endfont(out,pathonly);
	return result;
	}


static void outputchar(ostream &out, char ch)
	{
	if (ch == '(' || ch == ')' || ch == '\\')
		out << '\\';
	out << ch;
	}


/* switchfont() only switches fonts if they are actually 
 * different (they should both be the same size
 */
static void switchfont(ostream &out, char *font_old, char *font_new
 , double fontsize, int pathonly)
	{
	if (strcmp(font_old,font_new) != 0)
		{
		endfont(out,pathonly);
		startfont(out,font_new,fontsize);
		}
	}


/* This is used to get ready to make an overline, tilde, etc. on top
 * of some text.  It will leave on the PostScript stack:
 *   original x & y coords
 *   x_left, y_left, x_right, y_right   (coords of endpts of overline)
 * After calling this, do your overline, etc, then do moveto to
 * get back to original position and do startfont to get the
 * text going again.
 */
static void get_overline_coords(ostream &out, char *endptr, char *fontname
 , double fontsize , int pathonly)
	{
	char *outputobj(ostream &out, char *textptr, char *fontname, double fontsize
	 , int pathonly);

	endfont(out,pathonly);
	out << "CF dup 5 mul setflat\n";  // Don't waste printer memory
	out << "CPT\n";  // Store current location
	startfont(out,fontname,fontsize);
	outputobj(out,endptr,fontname,fontsize,1);
	endfont(out,1);
	out << "FP PBX\n";
	out << "7 -1 roll setflat\n";  // Restore to default flatness
	out << OVERLINE_SHIFT * fontsize << " add\n";  // Adjust vert pos
	out << "3 -1 roll pop dup 3 1 roll\n";  // make both y values same
	}


/* This assumes there is a font active when it starts
 *
 * Note: \overline causes it to construct the path for the chars to measure
 *  how much space they take up.  This eats printer memory - our printer
 *  has a limit of about 30 characters.
 */
static char *outputobj(ostream &out, char *textptr, char *fontname, double fontsize, int pathonly)
	{
	int idx, length, cnt;
	char *newtextptr;
	char *endptr;
	char newfontname[1024];

	if (*textptr == '\\')
		{
		++textptr;
		endptr = textptr;
		while (isalpha(*endptr))
			++endptr;
		length = endptr - textptr;
		   /* First, handle special control sequences - they
		    * are picked up by the "if" and "else if" parts.
		    * Anything that isn't handled in this part is handled in the
				* "else" which assumes anything in the table should be 
				* translated into the Symbol font.  Stuff not in the table is
				* sent "as-is".
		    */
		if (length == 5 && strncmp(textptr,"prime",length) == 0)
			{
			   /* Make the prime large (like TeX) by rescaling
			    * the font & shifting the coords.
			    */
			endfont(out,pathonly);
			out << "0 " << -.46*PRIMESCALE * fontsize << " RM2\n";
			startfont(out,SYMBOLFONT,PRIMESCALE*fontsize);
			out << "\\242";
			endfont(out,pathonly);
			out << "0 " << .46*PRIMESCALE * fontsize << " RM2\n";
			startfont(out,fontname,fontsize);
			return endptr;
			}
		else if (length == 5 && strncmp(textptr,"minus",length) == 0)
			{
			switchfont(out,fontname,SYMBOLFONT,fontsize,pathonly);
			out << '-';
			switchfont(out,SYMBOLFONT,fontname,fontsize,pathonly);
			return endptr;
			}
		else if (length == 3 && strncmp(textptr,"dag",length) == 0)
			{
			switchfont(out,fontname,(char *)"Times-Roman",fontsize,pathonly);
			out << "\\262";
			switchfont(out,(char *)"Times-Roman",fontname,fontsize,pathonly);
			return endptr;
			}
		else if (length == 4 && strncmp(textptr,"font",length) == 0)
			{
			if (*endptr != '{')
				{
				cerr << ERRSTR << "Expect '{fontname}' after \\font, but found ";
				cerr << '\'' << endptr << "'\n";
				exit(1);
				}
			++endptr;
			cnt = 0;
			while (*endptr != '}' && *endptr != '\0')
				{
				newfontname[cnt] = *endptr;
				++endptr;
				++cnt;
				}
			newfontname[cnt] = '\0';
			if (*endptr != '}')
				{
				cerr << ERRSTR << "Missing '}' in \\font{fontname}\n";
				exit(1);
				}
			switchfont(out,fontname,newfontname,fontsize,pathonly);
			endptr = outputobj(out,endptr+1,newfontname,fontsize,pathonly);
			switchfont(out,newfontname,fontname,fontsize,pathonly);
			return endptr;
			}	
		else if (length == 8 && strncmp(textptr,"overline",length) == 0)
			{
			   /* Do the overline by first constructing path for the text
			    * we are going to overline, then get bounding box and use
			    * to position the line.  Then re-create the text (yes,
			    * all text is generated twice - once for sizing, once
			    * for output).
					*
					* WARNING:  If already have pathonly==true, just don't output
					* anything - this is done because if we put the overbar in
					* the path, using "PBX" will pick up info about earlier
					* parts of the path & will screw things up.  The upshot of this
					* is that if you overline an object which contains an overline,
					* the contained overline is not included when the position of
					* the overline is calculated - this is a bug which probably
					* won't hurt much...
			    */
			if (!pathonly)
				{
				get_overline_coords(out, endptr, fontname, fontsize , pathonly);
				out << "NP M2 " ;
				out << OVERLINE_THICKNESS * fontsize << " SLW\n";
				out << "L2 ST\n";
				out << "M2\n";  // Now move back & draw the text under the overline
				startfont(out,fontname,fontsize);
				return outputobj(out,endptr,fontname,fontsize,pathonly);
				}
			return endptr;
			}
		else if (length == 9 && strncmp(textptr,"widetilde",length) == 0)
			{
			   /* The above comments for overline apply here too.
			    */
			if (!pathonly)
				{
				get_overline_coords(out, endptr, fontname, fontsize , pathonly);
				out << TILDE_HEIGHT * fontsize << " tilde fill\n";
				out << "M2\n";  // Now move back & draw the text under the overline
				startfont(out,fontname,fontsize);
				return outputobj(out,endptr,fontname,fontsize,pathonly);
				}
			return endptr;
			}
		else if (length == 14 && strncmp(textptr,"overrightarrow",length) == 0)
			{
			   /* The above comments for overline apply here too.
			    */
			if (!pathonly)
				{
				get_overline_coords(out, endptr, fontname, fontsize , pathonly);
				 // Draw the arrow head
				out << "2 copy 2 copy 4 -1 roll " << -ARROW_LENGTH*fontsize << " add\n";
				out << "4 1 roll " << ARROW_ANGLE << " arrow fill\n";
				 // Draw the stem of the arrow
				out << "2 1 roll " << -ARROW_LENGTH*fontsize << " add 2 1 roll\n";
				out << "NP M2 " ;
				out << OVERLINE_THICKNESS * fontsize << " SLW\n";
				out << "L2 ST\n";
				out << "M2\n";  // Now move back & draw the text under the overline
				startfont(out,fontname,fontsize);
				return outputobj(out,endptr,fontname,fontsize,pathonly);
				}
			return endptr;
			}
		else if (length == 8 && strncmp(textptr,"tildebar",length) == 0)
			{
			   /* The above comments for overline apply here too.
			    */
			if (!pathonly)
				{
				get_overline_coords(out, endptr, fontname, fontsize , pathonly);
				out << "4 copy\n";  // Copy coords for the tilde
				 // Make the overline
				out << "NP M2 " ; 
				out << OVERLINE_THICKNESS * fontsize << " SLW\n";
				out << "L2 ST\n";
				 // Make the tilde
				out << OVERLINE_SHIFT * fontsize << " add\n";
				out << "3 -1 roll " << OVERLINE_SHIFT * fontsize << " add 3 1 roll\n";
				out << TILDE_HEIGHT * fontsize << " tilde fill\n";
				out << "M2\n";  // Now move back & draw the text under the overline
				startfont(out,fontname,fontsize);
				return outputobj(out,endptr,fontname,fontsize,pathonly);
				}
			return endptr;
			}
		else  
			{  
			for (idx = sizeof(text2PS_syms)
			   /sizeof(struct text2PS_symbol_translation) - 1
			   ; idx >= 0 ; --idx)
				{
				if (strncmp(textptr,text2PS_syms[idx].insym,length) == 0
				   && (strlen(text2PS_syms[idx].insym) == length))
					break;
				}
			if (idx >= 0)  // have a match - map to something in Symbol font
				{
				endfont(out,pathonly);
				startfont(out,SYMBOLFONT,fontsize);
				out << text2PS_syms[idx].outsym;
				endfont(out,pathonly);
				startfont(out,fontname,fontsize);
				return endptr;
				}
			else  // no match (not in table) - send "as is"
				{
				outputchar(out,*textptr);
				return textptr + 1;
				}
			}
		}
	else if (*textptr == '{')
		{
		++textptr;
		while (*textptr != '}' && *textptr != '\0')
			textptr = outputobj(out,textptr,fontname,fontsize,pathonly);
		return textptr + 1;
		}
	else if (*textptr == '_')
		{
		endfont(out,pathonly);
		out << "CPT\n";
		newtextptr = outputsubscript(out,textptr+1,fontname,fontsize,pathonly);
		if (*newtextptr == '^')
			{
			out << "CPT pop\n"; // save x value
			out << "3 1 roll\n";  // push the x value to the bottom
			out << "M2\n";
			out << "CPT exch pop exch\n"; // save the y value & put before x
			newtextptr = outputsuperscript(out,newtextptr+1,fontname,fontsize,pathonly);
			   // move to start of normal text - compare x's & fetch y, then move
			out << "CPT pop max exch M2\n";  // now stack is empty
			}
		else
				// use old y & new x value
			out << "exch pop CPT pop exch M2\n";  // now stack is empty
		startfont(out,fontname,fontsize);
		return newtextptr;
		}
	else if (*textptr == '^')
		{
		endfont(out,pathonly);
		out << "CPT\n";
		newtextptr = outputsuperscript(out,textptr+1,fontname,fontsize,pathonly);
		if (*newtextptr == '_')
			{
			out << "CPT pop\n"; // save x value
			out << "3 1 roll\n";  // push the x value to the bottom
			out << "M2\n";
			out << "CPT exch pop exch\n"; // save the y value & put before x
			newtextptr = outputsubscript(out,newtextptr+1,fontname,fontsize,pathonly);
			   // move to start of normal text - compare x's & fetch y, then move
			out << "CPT pop max exch M2\n";  // now stack is empty
			}
		else
				// use old y & new x value
			out << "exch pop CPT pop exch M2\n";  // now stack is empty
		startfont(out,fontname,fontsize);
		return newtextptr;
		}
	else 
		{
		outputchar(out,*textptr);
		return textptr + 1;
		}
	}


/*
 * Note: Anything which would appear with a "\" in TeX must have
 * "\\" if it appears in C++ source code since C++ will strip one of
 * the backslashes.
 *
 * fontsize - size of font in points
 * fontname - name of Postscript font known by the printer (for normal text)
 */
void text2PS(ostream &out, char *textptr, double fontsize, char *fontname)
	{
	startfont(out,fontname,fontsize);

	do
		{
		textptr = outputobj(out,textptr,fontname,fontsize,0);
		} while (*textptr != '\0');

	endfont(out,0);
	}


/*
 * Note: Anything which would appear with a "\" in TeX must have
 * "\\" if it appears in C++ source code since C++ will strip one of
 * the backslashes.
 *
 * fontsize - size of font in points
 * fontname - name of Postscript font known by the printer (for normal text)
 * horizfract - put center at fraction "horizfract" of the total length 
 *   from the left
 * vertfract - put center at fraction "vertfract" of the total height 
 *   from the bottom
 *
 * This function is much less efficient than the text2PS function without
 * the horizfract and vertfract positioning options.  It also has a limit
 * of about 30 characters on our printer due to restriced memory for the
 * flattened path which is used to figure out how much space the text takes
 * up.
 */
void text2PS(ostream &out, char *textptr, double horizfract, double vertfract
   , double fontsize, char *fontname)
	{
	char *tmp;

	out << "CF dup 5 mul setflat\n";  // Don't waste printer memory
	out << "CPT\n";  // Store current location
	tmp = textptr;
	startfont(out,fontname,fontsize);
	do
		{
		tmp = outputobj(out,tmp,fontname,fontsize,1);
		} while (*tmp != '\0');
	endfont(out,1);
	out << "FP PBX\n";
	out << "3 -1 roll sub\n";  // Find delta_y
	out << "3 1 roll sub neg\n"; // Find delta_x
	out << -horizfract <<  " mul 2 1 roll " << -vertfract << " mul\n";
	out << "NP\n";
	out << "4 2 roll M2 RM2\n";
	out << "setflat\n";  // Restore to printer default flatness
	text2PS(out,textptr,fontsize,fontname);
	}


/*
 * This main() will dump a list of the "TeX like" symbols to the page
 */

#ifdef DUMPSYMBOLS

	int main()
		{
		int symnum, numsyms, col, row, numpercol;
		char buf[100];
	
#define COLS 3
#define FONTSIZE 12.
#define LMARGIN 100.
#define TOP 700.
#define WIDTH 450.
	
		cout << "%!\n";
		numsyms = sizeof(text2PS_syms) / sizeof(struct text2PS_symbol_translation);
		numpercol = numsyms / COLS + 1;
		cout << "%%BoundingBox: ";
		cout << LMARGIN << " ";
		cout << TOP - numpercol * FONTSIZE * 1.3 << " ";
		cout << LMARGIN + (COLS-1.)*WIDTH/COLS + .6*WIDTH/COLS + 2*FONTSIZE << " ";
		cout << TOP + FONTSIZE << "\n";
		cout << "% $Id: text2PS.C,v 2.5 2000/04/18 17:03:05 billd Exp $\n";
		for (symnum = 0; symnum < numsyms; ++symnum)
			{
			col = symnum / numpercol ;
			row = symnum % numpercol;
			cout << LMARGIN + col * WIDTH / COLS << " ";
			cout << TOP - row * FONTSIZE * 1.3 << " M2\n";
			sprintf(buf,"\\\\%s",text2PS_syms[symnum].insym);
			text2PS(cout,buf,FONTSIZE);
			sprintf(buf,"\\%s ",text2PS_syms[symnum].insym);
			cout << LMARGIN + col * WIDTH / COLS + .6 * WIDTH / COLS  << " ";
			cout << TOP - row * FONTSIZE * 1.3 << " M2\n";
			text2PS(cout,buf,FONTSIZE);
			}
		cout << "showpage\n" << flush;
		return 0;
		}
	
#endif
	
