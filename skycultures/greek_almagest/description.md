# Greek (Almagest)

## Introduction

<p>This ancient Greek sky culture is compiled in a book that is today known by its Arabic title "Almagest".
This book was written in Roman time (under the reign of Roman emperor Hadrian) at Alexandria (Africa) in
Greek language, with dates given in Egyptian month names and years counted after a Babylonian king,
so it is clearly a multi-cultural compendium of knowledge. It is a compilation of
astronomical knowledge of former astronomers including results from
observations and mathematical astronomy. Pieced together by Claudius
Ptolemy, using older, as well as his own, observations, it was written
in Greek, published in the Second Century and remained the main
astronomical work for the following 1500 years. It was originally written
with the title <i>Mathematike Syntaxis</i>, in Ancient Greek.
The name <i>Almagest</i>, meaning &ldquo;The Largest [Book]&rdquo;, was
developed from Arabian translations. To create this sky culture we used
the English translation by Toomer (1984), reworked it in some details
(e.g. using more literal translations from Greek instead of Latin terms that
are common today) and we made use of computer readable tables prepared
by Ernie Wright.</p>

## Description

The Almagest consists of 13 sections, called books. In the seventh
and eighth book, Ptolemy listed a total of 1022 stars in 48 constellations
(among which are about 5 star-like objects like globular star clusters).
It is a table of coordinates of the stars with a description of their
position in the constellation (such as "star at the elbow of X, longitude,
latitude, magnitude"). With regard to precession, Ptolemy used ecliptic
coordinates. As one of the first of his time, Ptolemy included the
magnitude, a quantitative scale of stellar brightness, probably adopted
from Hipparchus (which is not certain because Hipparchus&rsquo; catalog
is not preserved). The scale starts with the brightest star with the
magnitude of 1, going down to magnitude of 6, for the faintest stars
visible.

<p>For the computation of planet positions Ptolemy used a geocentric model
(which is allowed because the observer always stands on Earth) and, thus,
contributed to the scientific belief that the heliocentric model by
Aristarch was not needed. However, for the star catalogue of the
<i>Almagest</i> this does not matter at all because a star catalogue
always represents a sort of inventory of the fixed dots in the sky and
Ptolemy's proclaimed aim of the catalogue is to provide a list for making
a celestial globe (see Alm., VIII, 3). Being aware of precession he wants
to ease the business of future globemakers by using ecliptical coordinates:
Precession as known to Ptolemy shifts all stars parallel to the ecliptic,
therefore updates to the epoch of the respective globemaker could be
applied by a simple subtraction of the value for ecliptic longitude.</p>

### How this sky culture was made

### Star names

Out of more than 1,000 stars, Ptolemy mentions a proper name for only 15.
The rest are identified by fairly long descriptions such as "The star on
the end of the tail" for the Polaris. In order to avoid displaying such long
strings across the screen in Stellarium, we invented short labels for all
Almagest stars based on the constellation and the order in which they appear in
the catalogue.  For example, Polaris is given a designation "UMi 1" because
it is the first star in the constellation of Small Bear (UMi).  See the table
below for the correspondence between Ptolemy constellations and IAU abbreviations.
In addition, where Ptolemy describes a star as lying outside of the figure,
we use lowercase letters in the corresponding label. To see the long description
for a given star, users should enable "Use additional names of stars" in the
"View [F4]/Sky" settings and click on the star. The long description will then
be displayed at the top of the screen.

### Constellation lines

The process can be described as sketched here with the example of
Corvus:

In the constellation of Corvus (Raven), &alpha; Crv is the star in
the &quot;head of the raven&quot;. It is connected with the &quot;star
in the neck&quot;, &epsilon; Crv.  This one is connected with &quot;the
star in the breast&quot; &zeta; Crv.  From there two lines go to the
tips of the wings. &gamma; Crv is the star in the advanced wing and
&delta; Crv the star in the rear wing. From the star in the breast
another line goes to the &quot;foot of the raven&quot;, the star &beta;
Crv.

<p><img width="800" src="illustrations/corvus_s.png" /></p>
<p>After identifying the stars based on their coordinates and names, we
reconnected the stars according to the descriptions in the table
presented in the <i>Almagest</i>.</p>
<p>The names of stars and names of deep sky objects rely on the Almagest
only, e.g. Ptolemy uses the name &quot;&lambda;&alpha;&mu;&pi;&alpha;&delta;&#943;&alpha;&sigmaf;
(The Torch-like)&quot; for Aldebaran in his other work, the
<i>Tetrabiblos</i>, but this is not implemented in this sky culture because
it doesn't show up in the Almagest.</p>

The following table displays the original constellation name in Greek and its
English translation (column 2 and 3) and denotes our uncertainties in
the reconstruction (column 6).

<table>
<tr valign="top">
	<td><b>Abbreviation</b></td>
	<td><b>Original name</b></td>
	<td><b>Translation</b> (direct)</td>
	<td><b>IAU (Latin) name</b></td>
	<td><b>hints to constellation</b></td>
	<td><b>freedom of art</b></td>
</tr>
<tr valign="top">
	<td><notr>UMi</notr></td>
	<td><notr>&Mu;&iota;&kappa;&rho;&#942; &#702;&#714;&Alpha;&rho;&kappa;&tau;&omicron;&sigmaf;</notr></td>
	<td>Small She-Bear</td>
	<td><notr>Ursa Minor</notr></td>
	<td>like IAU constellation</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>UMa</notr></td>
	<td><notr>&Mu;&epsilon;&gamma;&alpha;&lambda;&#942; &#702;&#714;&Alpha;&rho;&kappa;&tau;&omicron;&sigmaf;</notr></td>
	<td>Great She-Bear</td>
	<td><notr>Ursa Major</notr></td>
	<td>like IAU constellation</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Dra</notr></td>
	<td><notr>&Delta;&rho;&#940;&kappa;&omega;&nu;</notr></td>
	<td>Dragon</td>
	<td><notr>Draco</notr></td>
	<td>all triangles or squares are vertebra or parts of the body; line at the head is the tongue</td>
	<td></td>
</tr>
	<tr valign="top">
	<td><notr>Cep</notr></td>
	<td><notr>&Kappa;&eta;&phi;&epsilon;&#973;&sigmaf;</notr></td>
	<td>Kepheus</td>
	<td><notr>Cepheus</notr></td>
	<td>king, upside down </td>
	<td>three head stars are tiara; &beta; seen as part of the belt, although Almagest says beneath belt</td>
</tr>
<tr valign="top">
	<td><notr>Boo</notr></td>
	<td><notr>&Beta;&omicron;&#974;&tau;&eta;&sigmaf;</notr></td>
	<td>Ploughman</td>
	<td><notr>Bo&ouml;tes</notr></td>
	<td>has a shepherd's staff in his hand (&omega;)</td>
	<td>star HIP 72582 added as neck star</td>
</tr>
<tr valign="top">
	<td><notr>CrB</notr></td>
	<td><notr>&Sigma;&tau;&#941;&phi;&alpha;&nu;&omicron;&sigmaf;</notr></td>
	<td>Crown</td>
	<td><notr>Corona Borealis</notr></td>
	<td>like IAU constellation; no details for lines in the text</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Her</notr></td>
	<td><notr>&#703;&Epsilon;&nu;&gamma;&#972;&nu;&alpha;&sigma;&iota;&nu;</notr></td>
	<td>Kneeler</td>
	<td><notr>Hercules</notr></td>
	<td>one of the foot stars is top of staff of Bootes</td>
	<td>star HIP 82764 added as neck star</td>
</tr>
<tr valign="top">
	<td><notr>Lyr</notr></td>
	<td><notr>&Lambda;&#973;&rho;&alpha;</notr></td>
	<td>Lyre</td>
	<td><notr>Lyra</notr></td>
	<td></td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Cyg</notr></td>
	<td><notr>&#702;&#714;&Omicron;&rho;&nu;&iota;&sigmaf;</notr></td>
	<td>Bird</td>
	<td><notr>Cygnus</notr></td>
	<td>swan with legs</td>
	<td>Tips of wings connected with tail</td>
</tr>
<tr valign="top">
	<td><notr>Cas</notr></td>
	<td><notr>&Kappa;&alpha;&sigma;&sigma;&iota;&#941;&pi;&epsilon;&iota;&alpha;</notr></td>
	<td>Kassiepeia</td>
	<td><notr>Cassiopeia</notr></td>
	<td>Queen sitting on a throne</td>
	<td>to avoid confusion we did not draw the throne</td>
</tr>
<tr valign="top">
	<td><notr>Per</notr></td>
	<td><notr>&Pi;&epsilon;&rho;&sigma;&epsilon;&#973;&sigmaf;</notr></td>
	<td>Perseus</td>
	<td><notr>Perseus</notr></td>
	<td>Double star cluster NGC 869 and NGC 884 as Deep Sky Object - &gt;one of the stars in the cluster was used for drawing</td>
	<td>one of the stars in Gorgon-head is added to make the head look more spherical</td>
</tr>
<tr valign="top">
	<td><notr>Aur</notr></td>
	<td><notr>&#703;&Eta;&nu;&#943;&omicron;&chi;&omicron;&sigmaf;</notr></td>
	<td>Charioteer</td>
	<td><notr>Auriga</notr></td>
	<td>wears long garment; garment limited through shoulders and hem</td>
	<td>&omicron; Aur added as neck star; 1 Aur added as hem star</td>
</tr>
<tr valign="top">
	<td><notr>Oph</notr></td>
	<td><notr>&#702;&Omicron;&phi;&iota;&omicron;&#973;&chi;&omicron;&sigmaf;</notr></td>
	<td>Serpent Bearer</td>
	<td><notr>Ophiuchus</notr></td>
	<td>has serpent in his hand</td>
	<td>a star added as neck star</td>
</tr>
<tr valign="top">
	<td><notr>Ser</notr></td>
	<td><notr>&#702;&#714;&Omicron;&phi;&iota;&sigmaf;</notr></td>
	<td>Snake</td>
	<td><notr>Serpens</notr></td>
	<td>two separate parts of the snake (head and tail); square is head</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Sge</notr></td>
	<td><notr>&#702;&Omicron;&iota;&sigma;&tau;&#972;&sigmaf;</notr></td>
	<td>Arrow</td>
	<td><notr>Sagitta</notr></td>
	<td>Like IAU constellation, &eta; Sge is missing </td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Aql</notr></td>
	<td><notr>&#702;&Alpha;&epsilon;&tau;&#972;&sigmaf;</notr></td>
	<td>Eagle</td>
	<td><notr>Aquila</notr></td>
	<td>&tau; Aql as head star, &beta; as neck, Altair is between shoulders, &gamma; and &mu; are shoulders</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Del</notr></td>
	<td><notr>&Delta;&epsilon;&lambda;&phi;&#943;&sigmaf;</notr></td>
	<td>Dolphin</td>
	<td><notr>Delphinus</notr></td>
	<td></td>
	<td>refined shape</td>
</tr>
<tr valign="top">
	<td><notr>Equ</notr></td>
	<td><notr>&Pi;&rho;&omicron;&tau;&omicron;&mu;&#942;</notr></td>
	<td>Bust [of a horse]</td>
	<td><notr>Equuleus</notr></td>
	<td></td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Peg</notr></td>
	<td><notr>&#703;&#714;&Iota;&pi;&pi;&omicron;&sigmaf;</notr></td>
	<td>Horse</td>
	<td><notr>Pegasus</notr></td>
	<td>with mane and one wing</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>And</notr></td>
	<td><notr>&#702;&Alpha;&nu;&delta;&rho;&omicron;&mu;&#941;&delta;&alpha;</notr></td>
	<td>Andromeda</td>
	<td class='latin'><notr>Andromeda</notr></td>
	<td>dress and belt</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Tri</notr></td>
	<td><notr>&Tau;&rho;&#943;&gamma;&omega;&nu;&omicron;&sigmaf;</notr></td>
	<td>Triangle</td>
	<td><notr>Triangulum</notr></td>
	<td>four given stars &#61664; middle star of one side</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Ari</notr></td>
	<td><notr>&Kappa;&rho;&iota;&#972;&sigmaf;</notr></td>
	<td>Ram</td>
	<td><notr>Aries</notr></td>
	<td>turned head; only one horn</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Tau</notr></td>
	<td><notr>&Tau;&alpha;&upsilon;&#771;&rho;&omicron;&sigmaf;</notr></td>
	<td>Bull</td>
	<td><notr>Taurus</notr></td>
	<td>half body, only two legs visible; direction of view to observer</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Gem</notr></td>
	<td><notr>&Delta;&#943;&delta;&upsilon;&mu;&omicron;&iota;</notr></td>
	<td>Twins</td>
	<td><notr>Gemini</notr></td>
	<td>one star in common; touching each other with hands</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Cnc</notr></td>
	<td><notr>&Kappa;&alpha;&rho;&kappa;&#943;&nu;&omicron;&sigmaf;</notr></td>
	<td>Crab</td>
	<td><notr>Cancer</notr></td>
	<td>square body</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Leo</notr></td>
	<td><notr>&Lambda;&#941;&omega;&nu;</notr></td>
	<td>Lion</td>
	<td><notr>Leo</notr></td>
	<td>opens jaw</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Vir</notr></td>
	<td><notr>&Pi;&alpha;&rho;&theta;&#941;&nu;&omicron;&sigmaf;</notr></td>
	<td>Maiden</td>
	<td><notr>Virgo</notr></td>
	<td>no separate head</td>
	<td>fainter stars added to draw the wings</td>
</tr>
<tr valign="top">
	<td><notr>Lib</notr></td>
	<td><notr>&Chi;&eta;&lambda;&alpha;&#943;</notr></td>
	<td>Claws [of the Scorpion]</td>
	<td><notr>Libra</notr></td>
	<td>Ptolemy always uses the term &quot;claws&quot;, never &quot;the balance&quot;.</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Sco</notr></td>
	<td><notr>&Sigma;&kappa;&omicron;&rho;&pi;&#943;&omicron;&sigmaf;</notr></td>
	<td>Scorpion</td>
	<td><notr>Scorpius</notr></td>
	<td></td>
	<td>arms added around the head: &nu; and &rho;</td>
</tr>
<tr valign="top">
	<td><notr>Sgr</notr></td>
	<td><notr>&Tau;&omicron;&xi;&#972;&tau;&eta;&sigmaf;</notr></td>
	<td>Archer</td>
	<td><notr>Sagittarius</notr></td>
	<td>a centaur with  bow ahead; &bdquo;cloak&ldquo; behind</td>
	<td>we included many faint stars in our stick figure in order to make the picture clear.</td>
</tr>
<tr valign="top">
	<td><notr>Cap</notr></td>
	<td><notr>&Alpha;&#943;&gamma;&#972;&kappa;&epsilon;&rho;&omicron;&sigmaf;</notr></td>
	<td>The One with the Goat's Horn</td>
	<td><notr>Capricornus</notr></td>
	<td>fish tail; two legs visible</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Aqr</notr></td>
	<td><notr>&#703;&Upsilon;&delta;&rho;&omicron;&chi;&#972;&omicron;&sigmaf;</notr></td>
	<td>Water-Carrier</td>
	<td><notr>Aquarius</notr></td>
	<td>water out of jug</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Psc</notr></td>
	<td><notr>&#702;&Iota;&chi;&theta;&#973;&epsilon;&sigmaf;</notr></td>
	<td>[2] Fish</td>
	<td><notr>Pisces</notr></td>
	<td></td>
	<td>northern fish: 68(h), 67(k), and 65(i) described as head in Almagest but we took them as fin because mouth should be at g and &tau; Psc. Additional change on tail fin: extended to &rho;</td>
</tr>
<tr valign="top">
	<td><notr>Cet</notr></td>
	<td><notr>&Kappa;&eta;&#771;&tau;&omicron;&sigmaf;</notr></td>
	<td>Sea Monster</td>
	<td><notr>Cetus</notr></td>
	<td></td>
	<td>Body does not go through star &tau;, but through star &upsilon;</td>
</tr>
<tr valign="top">
	<td><notr>Ori</notr></td>
	<td><notr>&#702;&Omega;&rho;&#943;&omega;&nu;</notr></td>
	<td>Orion</td>
	<td class='latin'><notr>Orion</notr></td>
	<td></td>
	<td>The &quot;head&quot; is labeled as &quot;nebulous&quot; which means Ptolemy interpreted &phi;<sub>1</sub>, &phi;<sub>2</sub>, and  &lambda;, together with fainter stars between them as a &quot;cluster&quot; (or association which is more extended than the modern &quot;&lambda; Ori Assoc.&quot;). Head does not have direct connection to the shoulder stars anymore, but a connection to a star between the stars in the shoulders.</td>
</tr>
<tr valign="top">
	<td><notr>Eri</notr></td>
	<td><notr>&Pi;&omicron;&tau;&alpha;&mu;&omicron;&#972;&sigmaf;</notr></td>
	<td>River [nameless]</td>
	<td><notr>Eridanus</notr></td>
	<td>Like IAU constellation, but shorter</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Lep</notr></td>
	<td><notr>&Lambda;&alpha;&gamma;&omega;&#771;&sigmaf;</notr></td>
	<td>Hare</td>
	<td><notr>Lepus</notr></td>
	<td></td>
	<td>took the "4 stars over the ear" as ear</td>
</tr>
<tr valign="top">
	<td><notr>CMa</notr></td>
	<td><notr>&Kappa;&#973;&omega;&nu;</notr></td>
	<td>Dog</td>
	<td><notr>Canis Major</notr></td>
	<td></td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>CMi</notr></td>
	<td><notr>&Pi;&rho;&omicron;&kappa;&#973;&omega;&nu;</notr></td>
	<td>The One before the Dog</td>
	<td><notr>Canis Minor</notr></td>
	<td></td>
	<td>In Almagest, the name of the constellation is &quot;The One before the Dog&quot; or &quot;Harbinger of Sirius&quot; as Toomer puts it. However, &beta; CMi is called &quot;the neck&quot; (of whom is unknown).</td>
</tr>
<tr valign="top">
	<td><notr>Arg</notr></td>
	<td><notr>&#702;&Alpha;&rho;&gamma;&omega;</notr></td>
	<td>Ship &quot;Argo&quot;</td>
	<td><notr>Argo</notr></td>
	<td>smaller than the sum of the IAU-constellations Pup+Pyx+Car+Vel</td>
	<td>Many stars not integrated in the constellation, to create a boat-like shape; in many depictions (including the ancient Farnese globe), only a half of a ship is painted.</td>
</tr>
<tr valign="top">
	<td><notr>Hya</notr></td>
	<td><notr>&#703;&#714;&Upsilon;&delta;&rho;&omicron;&sigmaf;</notr></td>
	<td>Water Snake</td>
	<td><notr>Hydra</notr></td>
	<td>like IAU constellation</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Crt</notr></td>
	<td><notr>&Kappa;&rho;&alpha;&tau;&#768;&eta;&rho;</notr></td>
	<td>Krater (vessel)</td>
	<td><notr>Crater</notr></td>
	<td></td>
	<td>a Krater is special Greek wine mixing vessel which looks like an amphora or vase: <a href="https://en.wikipedia.org/wiki/Krater">https://en.wikipedia.org/wiki/Krater</a> Ptolemy describes only one star in the foot (&alpha; Crt) and two handles (&eta;, &theta; Crt)</td>
</tr>
<tr valign="top">
	<td><notr>Crv</notr></td>
	<td><notr>&Kappa;&oacute;&rho;&alpha;&xi;</notr></td>
	<td>Raven</td>
	<td><notr>Corvus</notr></td>
	<td>like IAU constellation</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>Cen</notr></td>
	<td><notr>&Kappa;&#941;&nu;&tau;&alpha;&upsilon;&rho;&omicron;&sigmaf;</notr></td>
	<td>Kentauros</td>
	<td><notr>Centaurus</notr></td>
	<td></td>
	<td>deviation from description: HIP 65373 instead of &omega; Cen (cluster) taken as star on the back. &lsquo;Thyrsus&lsquo; not drawn (to avoid confusion), backward arm added.</td>
</tr>
<tr valign="top">
	<td><notr>Lup</notr></td>
	<td><notr>&Theta;&eta;&rho;&#943;&omicron;&nu;</notr></td>
	<td>Beast</td>
	<td><notr>Lupus</notr></td>
	<td></td>
	<td>&beta; described as &lsquo;End of hind leg&lsquo; -> taken as star in the belly; &tau;<sub>1</sub> as hindleg; &chi; in head, because otherwise shapelessness arises; HIP 73493 taken as foreleg</td>
</tr>
<tr valign="top">
	<td><notr>Ara</notr></td>
	<td><notr>&Theta;&upsilon;&mu;&iota;&alpha;&tau;&#942;&rho;&iota;&omicron;&nu;</notr></td>
	<td>Altar</td>
	<td><notr>Ara</notr></td>
	<td>like IAU constellation</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>CrA</notr></td>
	<td><notr>&Sigma;&tau;&#941;&phi;&alpha;&nu;&omicron;&sigmaf; &Nu;&#972;&tau;&iota;&omicron;&sigmaf;</notr></td>
	<td>Southern Crown</td>
	<td><notr>Corona Australis</notr></td>
	<td>like IAU constellation; only uncertainty with stars that only got a BSC number in the Almagest, because these are not clearly to identify in Stellarium</td>
	<td></td>
</tr>
<tr valign="top">
	<td><notr>PsA</notr></td>
	<td><notr>&Nu;&#972;&tau;&iota;&omicron;&sigmaf; &#702;&Iota;&chi;&theta;&#973;&sigmaf;</notr></td>
	<td>Southern Fish</td>
	<td><notr>Piscis Austrinus</notr></td>
	<td>the fish is laying on his back</td>
	<td>the fish is apparently dead: the belly up, or an eelwith twisted spine; we added a few stars to mark the tail fin whose tip is given as &beta; PsA.</td>
</tr>
</table>

### Fair Use

This sky culture originates from a student's year of research. We provide this for free but
authors of contributions certainly deserve to be cited according to the common rules. Thank you!

### Thanks

The authors thank Patrick Gleason and Georg Zotti for English proofreading and interesting discussions.

## References

 - [#1]: Grasshoff, G.: The History of Ptolemy's Star Catalog, Springer, New York, 1990
 - [#2]: Heiberg, J. L. (Ed.): Claudii Ptolemaei: Syntaxis Mathematica, Teubner, Leipzig, 1898
 - [#3]: Hoffmann, S. M.: Hipparchs Himmelsglobus, Springer, Wiesbaden / New York, 2017
 - [#4]: Toomer, G. J.: Ptolemy's Almagest, Duckworth, London, 1984
 - [#5]: [Ernie Wright: Seeing Ancient Stars, Visualization of the Almagest Catalog, 2006](http://www.etwright.org/astro/almagest.html#cat)

## Authors

This sky culture was compiled and added to Stellarium by Alina Schmidt, Lea Jabschinski, Marie von Seggern and Susanne M. Hoffmann: service@uhura-uraniae.com

Written in English: the authors

## License

CC BY-ND 4.0
