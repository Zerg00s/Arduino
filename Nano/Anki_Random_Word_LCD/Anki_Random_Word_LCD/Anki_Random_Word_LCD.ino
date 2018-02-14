// DISPLAY RANDOM ANKI NOTE ON THE LCD DISPLAY
// WITH A BUTTON FOR SWITCHING DECKS

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Kuman 0.96 inch I2c Serial LCD Display:
// SDA - A4
// SCL - A5

// Connect button to D2 with a pull up resistor

volatile byte state = HIGH;
const byte interruptPin = 2;

const char CpeDeck[] PROGMEM = {"avid\rhackneyed\rmundane\rcompulsive\rcorny\rcliffhanger\ratrocious\rtopical\rcontrived\rtake it or leave it\rgritty\roff the mark\rgo round the houses\rdone and dusted\rtake a chill pill\rsleep on it\rdeceased\ra dirt road\rdraw up\rsiding (a)\rdare sb to do sth\rstoker\rto toss (sb sth)\rtin\runattainable\rthrashing\rclutterd with sth\ra thornbill\ra molope\rto wail\rcherished\rfuzzy\rhaunting\rtraumatic\rlingering\rfleeting\rrekindle a memory\rpush sth aside\rstir memories/emotions\rtrigger a memory\rconjure sth up\rblock sth out\rblot sth out\rblow your own trumpet\rtentative\revocative\rat the crack of dawn\rto hedge\rhedge your bets\rbeat sb fair and square\rsangfroid\rto feign\rto gloat\rfreak\rdismal\ra sash window\runfazed (by)\rportly\rlike a top\ra bowler hat\rpin-striped\rcareworn\rbode well/ill\rmorosely\rruckus\rto savour\rto scheme\rself-proclaimed\rget wind of\rencompass\rdumbstruck\rit's odds on\rlive and let live\rhoax\ra gerbil\rto bleat\rto chortle\rgruelling\rdismay\rChancellor of the Exchequer\rto prise\rsopping wet\rAxminster\rto rant\rfill somebody in\rto fill in time\rfill in for somebody\ramber\rharrassed\rto splutter\rhoarsely\rflustered\rfretful\rto grope\rcast about\rstab of fear\rto eclipse\rto smug\r(a) dip\ra combo\ra lust\rto lust after\rservitude\rto flog\reerie\rthrust\rto tap (into)\rdistil / distill\rbe/look old hat\rto draw (with)\rto draw on/upon sth\ra mound\rto swipe\rto tickle sb into\ra knuckle\rto rap/a rap\ra rap on\ranew\rcentre on/upon something\ra dweeb\rdreary\rludicrous, ludicrously\rlovable / loveable\ra lunk (slang)\rto nip\rfinesse / to finesse\rbe part and parcel of something\ra touch\rto thump\rfruition (formal)\ra dystopia\rgroundbreaking\rfestive\rhooked (informal)\rsurreptitiously\roverstatement\rtwirl\rhavoc\rwreak (to)\rGood greif!\rrigging\rto colour (up)\rto cave in to sth\ratrocity plural atrocities\rto elude\rto stamp\ran ice bucket\rto uproot\rto grimace\rto baffle\rhave a field day (informal)\rleft, right, and centre\rOnce upon a happier time\rdawning horror\rto swoop\rweak-kneed\rattempt AT (doing) sth\rAT the first/second attempt\rshrunken\rto budge\raggrieved\rto flinch\ra grate\rstreaks\ra mane\rtawny\rrangy\rshrewd\ra keyhole\ra lookout\ra flicker of\raddle brains\rrear (up)\rscrawny\rwary\rlose one's bearings\ra quarry\rrailing\rdilapidation\rdunghill\rto snarl\radmonitory\rto board up\rstrained\rthreadbare\rrickety\rvermin\rhunchback\rto simper/ a simper\rto caress\rto wince\rto crave\rto scurry\rto glower\rto discompose\rto hoodwink\rdiscomfit\rforestall\ra stint\ra stooge\rto thwart sb\rto inflect\rto apportion\rinvincible\rto dispose of\rto rally\rrally around\ra tight corner\robnoxious\rallegiance\rspin-spun-spun\rscathing\rtherein\rto seep\rdouse , dowse\rto jerk\rbe in on sth\rto stoop to\rto steer\rto slop\rcackle\ra windowpane\rfug\rshock (a)\rsmattering\rsmattering of\rhiggledy-piggledy\rtangled (up)\rblare (out)\rfabled\rhitherto\rrife\rctd.\rravage\rrift\rreinstate\rto surface\rstringent\rarray\rtask force\rto survey\rto swivel\rresidue\rtrespass (a)\ra stand\rto coat\rto masquerade\ra squad\rbreadcrumbs\rto/of no avail\rlopsided\rto slant\rto furl\ra missive\rto shrug sth off\rto go astray\rto lead sb astray\rto billow\rto lob\rpanicky\rto clamber\rto wrench\remblazoned\rto allot\rallotment\r\0"};
const char N1984Deck[] PROGMEM = {"vile\rto nuzzle\rtack to\rulcer\rpig-iron\roblong\rplaque\rmeagreness\rcoarse\reddy\rto plaster\ralternately\ra snoop\rto babble away\rguesswork\rconceivable\rgrimy\rOceania\rvista\rbalk (noun)\rsag\rsordid\rtableau\rramifications\rbarbed wire\rtruncheon\rhunk\rnitric acid\rincautious\ralcove\rfrowsy\rslummy\rnib\rtremor\rbowel\rconstricted\rformidable\rsandy-haired\rrenegade\rbackslider\rtraitor\rdefile\rto hatch\raureole\rgoatee\rdespicable\rinherent\rsenile\rlevel-headed\rpolysyllable\rspecious\rclaptrap\rto tramp\rdupe\rto refute\rsaboteur\rconspirator\rclandestine\rinexorably\rlucid\rrung\rsledgehammer\rvindictive\rblowlamp\rto deride\rto venerate\rravish\rsupple\rchastity\rdin\rtremulous\rtomtom\rentrails\rconceivably\rinscrutable\rinconceivable\requivocal\rto belch\rvoluptuously\rtwinge\rdodge\rannihilated\rfutile\rsmudge\rwispy\rwhine\rcountenance\rcrease\rthereabouts\rdingy\rbattered\rtrample\rimpedimenta\rdog-eared\rcomb\rreek\rdrudge (to)\rstatutory\rput in an appearance\rspanner\rinvertebrate\rneckerchief\rgambol\rcaper\rto clamour\rcatapult, slingshot\rrelish\rpartisanship\rtorasp\rreverberate\renvelop\rloophole\rquail\rbatter down a door\rrasp\r\0"};
const char Dota2Deck[] PROGMEM = {"impetuous\rpyroclasm\rdefilement\rstoke\rfurnace\rfestoon\rcauterize\rtarnation\rcelestial\remp\rdesiccated\rfabrication\rarcane\rincantation\rabound\raugury\rtedium\rUnto\rAvowedly\rforthwith\rWellaway\rthus and so\rWhithersoever\rto pluck\rarcana\rWrung out\ralacrity\rnowise\rperturbation\rinfelicitous\rtwas\rinsipid\rmote\rtabulation\rnary\rbeget - begat\rnuncupatory\r fall to sb\rrancid\rfornicate\ratone\rfurtive\rto cramp\rexpedite\rsturdy\rwoe\rpertain\rguillemot\rlaud\rsubliminal\rimpetus\rcorrugated\rfraught (with)\rsubliminal\rpertain\rhoodwink\rretinue\rbe in for a treat\rsigil\rcrescent\rabode\rpromulgate\rpursuant\rcallus\rcrumple (up)\rparasol\rdigger\rserenity\roblique\rabstruse\requanimity\rboor\runcouth\rminted\rbrash\rfaux pas\rfrothy\rbaulk = balk at\rsequin\rcompatriot\rconstrue\rloonie\rtoady\rchaise longue\rwoo\rsubstantive\rmerits\rcoalesce\rMountie\rporcelain\rstopgap\rto spur\rmull\rexacerbate\rostensibly\rlax\rdraw a blank\rIRL\rriffraff\rtranscendent\raustere\rmeticulous\rvivacious\rfat cat\rinextricably\ron end\rPacifier/Soother/Binky\rlateral thinking\raffix\rcull/culling\raliment\rresidual\rdistended\rwedge\rexpedient\rcollateral\rimpervious (to)\rpreponderance\rreveller\rbone of contention\rshenanigan/shenanigans\rsomber\rstag/ staggete\rtreasure trove\rproponent\rclandestine\rchiton\rcarnage\rnonchalant\rTweeps\rspleen\rinsidious\rknockoff\rsentiment\rtorpor\rcontagion\rcoercion\rschism\rdisciple\rstop short of\rghoul\rheckle\rramshackle\rstanding\rwiener\rMacaroon\rnapa\rtinsel\rstencil\rpock\rproboscis\rsturgeon\rdowny\rferal\rcinch\rseverance\rprude\rQuotient\rcedar\rramification\rpremidiation\raccolade\rinexorable\rcadence\rdeciduous\rà la carte\rhoe\rapron\rwafer board\riris\rstamen\rcontiguous\rtearjerker\rnoose\rtip smth over\rturd\rtwat\rimbibe\ramalgamate\rdaft\rvanquish\rfastidious\rleeway\rremediate\rmeek\rculprit\rexonerate\rbenevolent\rinnocuous\rconstituent\rtransient\rtranspire\rforlorn\rhone\raltercation\rguardrail\rpromiscuous\rBronco\rbells and whistles\rtenacity\rcondone\rvisceral\requinox\rdiscombobulated\rscaffold\rshirk\rpail\raplomb\rhunch\rinnuendo\rslew\rpsych (to)\rloon\rdeviant\rimpertinent\rapartheid\rpantry\raplomb\rscaffold\rshirk\requinox\rserf\rcogent\rindolent\rimpervious to\rto waylay\rsentinel\rtrinket\rrecrimination\rdiscombobulated\rentail\roatmeal\rto prod\rcaucus\rindictment\rflounder\rvisceral\rlather\rpreclude\rhideout\rbreak the mould\rambivalent\rmisogynist\raspiring\rCaucasian\rcolander\rottoman\rfaux\rdichotomy\rfilibuster (to)\rrelinquish\rsycophant\rreciprocal\rextrude (to)\rabsolve\rdoily\rticker\rtake a wiz\rrunt (a)\rsnoot (a)\r'hit me'\r'get the boot'\rdeadbeat\rcirca\rbuck up\rmow down\rpissy\rlayaway (a)\rspiel\rrecluse\rsales pitch\rtoodles\rgrouchy\rto dust off\rbe in a jam\rcelerity\rserene\ramp up\rit's your call\raddle-pate, addle-head\rway station\rtwitchy\r'tea and biscuits'\rtraipse (to)\rbounce it down to (email)\rsandries\rgiddy\rmite\rto take umbridge\rhull\ra spell\rto haul anchor\ron the level\rwithout rudder\rteam smb down\ra tick\rho!\rchicken comes to roost\rfried (electronincs)\rmeld (to)\ramp up\rbona fide\rlace\rpick it up!\rto sleep away\r'dig in'\rdrama queen\rout with it\rhissy fit\rcinch in\rtramp (a)\rmarch to your own drum\rinvoke (law)\rmews\rshuttle diplomacy\ra dime\rnickel\rdeath knell\rknock yourself out\rslush fund\rprima donna\reat off my hand\rplunger\rpansy\rpocket rocket\ra hoot\rtwenty\rtrucker\rinterminable\rpain point\rgating\rsaline\rwhiplash\rmeeple\rgarnish\rtrite\rstodgy\rdowdy\rskittish\rconsort\rupstairs outsidies\rhaphazard\rmicrofiche\rbehest\rdairy\raficionado\rnitpicking\ryokel\rtarmac\rvagrant\rsalient\rundue influence\rby (or in) virtue of\rupshot\rUpshot\rUsurious\rgaggle\rcynosure\rbush league\rsterling (adj)\rpleats\rravishing\rdabble (to)\rbaloney\rsaucy\rwhen in Rome do as romans do\rto keep smb in line\r3 fingers\rditty (a)\rsteed\rfondue\rpunt (to)\rflip off (to)\rbrawn (a)\rmake whoope\rto brown bag\ryour ass is grass\rdo something rash\rto be in a pickle\rdown with smth\rto blubber\rimpending\rthang (70's)\ryou got soul\rfeisty\rpray tale\rfunk, funky\rto go head to head\rto have a throw down\rhead honcho\rtight ass (butt)\rpatootie\rya'll\rconniption\rto be on to smth.\rto sit on the sidelines\rlet's bounce\rto play yourself\rhot to trot\rlay into someone\rTo have a bone to pick with sbd\rBlack Bottom\rdog's dinner\rTangential\runderfoot\rpate\rpilfer (to)\rleery\rforthcoming\rculpable\rkeep tabs on\rcontrite (adj)\rfume (to)\rcovenant (a)\rbroadleaf plantain\rfern\rlilac\rcamomile\rthistle\rknotgrass\rhedging cedar\rdog rose\rrowan tree\rchokeberry\racacia\rlinden\rorchid\rwhisk\rcollie\rdachshund\rMoose\rcrosswalk\rbarrister\rback-of-the-envelope\rassuage\rto boil the ocean\rI am in good company\ra one\rpoppet\rhag\rdollars to donuts\rjuxtaposition\rloaded question\rby the same token\reviscerated\rsedition\rimpunity\rgutted\rmidwife\rdisused\raloof\rtidings\rhomunculus\rambulate (to)\rValhalla\rcovenant\rstrut\rreel\rdeclension\ruplink\rillustrious\rpeg (to)\rmesa\rclaw hammer\rrapacious\rhaemostasis\rhaven\rrockery\rvirility\rtaxi (to)\rpropensity\rrut\rblowhard\rwater jug\rknead\rrear (to)\rsnoop\rburdock\rastringent\rserendipity\rgregarious\rattenuate\rostentatious\rjuxtaposition\rharlot\rCamera obscura\rprecept\rPro bono (publico)\r\0"};
const char FahrenheightDeck[] PROGMEM = {"ruled paper\rallusion (to)\rsalamanders\rbrass\rnozzle\rtatters\rin tatters\rstolid\rmarshmallow\rporch\rto singe\rminstrel\rflue\rto waft\rgrille\rtallow\rthimble\rfringe\retch\rtamp\rseam\rpulverize (to)\rstratum\rbore\rserum\roveralls\rmallet\rcontra-sedative\rpuff adder\rsludge\rcleanse\rweave\rfrench window\rwad (to)\rcoat-tails\rjersey\rspout (to)\rlozenge\rdopy (dopey)\rheck\rolfactory\rproboscis\rprocaine\rincinerator.\rbunk\rto rasp\rcog\rsimmer\rfaceted\rsulphur\rcinnamon\rfunnel\rspout\rhubcap\rto spank\rswell!\rshin\rdrone\rproclivity\rcinder(s)\rthunderhead\rgibber\rcymbals\rtitillation\rspeck\rquibble\rin memoriam\rpagan\rodd duck\rnip in the bud\rIowa\rcombustible\requate\rbestial\rdaredevil\rtheremin\rdyke , dike\rgullet\ralkaline\rshovel\rcinnamon\rfunnel\rspout\rto spank\rswell!\rto shin\rdrone\rproclivity\rcinder\rto flake\rsheath\rodious\rslicker\rto rollick\rgilt\rabyss\rravenous\rto tamp\rfathom\rgibber\rtendon\rmantis\rpount\rto fidget\ra gag\rto fling\rpratfall\rto yank\rnavel\rtapioca\rdictum\rcower\rcymbal\rto sizzle\rchar\rsieve\rcadence\rnutmeg\r\0"};
const char LokeDeck[] PROGMEM = {"miser\rinauspicious\rkneecap\rlarceny\rmongrel\rmausoleum\rclothyard shaft\rwink at something\rnamesake\rpestilence\riodine\rdoublet\rto jab\rsternum\rmortician\rto inter\rgaudy\rcommensurate\revery nook and cranny\rtendril\rgrotty\rthresh\rlentil\rstale\rhanger-on\rinnards\rthrong\rasp\rmagnanimous\rkicker\rshaft\rlard\roddments\rderisive\rginger\rpunitive\rhem\rto haul\rbodice\rto veer\rtenement\rto jut\rtier\rtraverse\rhovel\rjut\rwalk abreast\rwarped\rpatron\rexodus\rdetritus\rgarnet\rhaul (noun)\rcircumspect\rruefuladjective\ropulent\rcarmine\razure\rdecrepit\reldritch\rscrievener\rcraggy\rvestment\rtaut\rinstill\rschmuck\rhobbled\rpomander\rfoul (to)\rpulley\rheadstand\rhandstand\rseamstress\ramethyst\rmaking muffins (cat)\r\0"};
const char * const AnkiDecks[] = { CpeDeck , N1984Deck , Dota2Deck, FahrenheightDeck, LokeDeck };
//32 10 13 == " \n\r" == SPACE,  Line feed (LF),  Carriage return (CR)

int NumberOfDecks = 0;
int CurrentDeck = 2;
long randNumber;

void setup()
{
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect. Needed for native USB
  pinMode(interruptPin, INPUT);  //on
  attachInterrupt(digitalPinToInterrupt(interruptPin), button_pressed, RISING);
  randomSeed(analogRead(0));
  NumberOfDecks = (sizeof(AnkiDecks) / sizeof(char *));
  CurrentDeck = random(0, NumberOfDecks);
}

void loop()
{
  printRandomNote();
  delay(2600);
}

int getSize(char* ch) {
  int counter = 0;
  int myChar = 0;
  do {
    myChar =  pgm_read_byte_near(ch + counter);
    if (myChar == 0) {
      return counter;
    }
    counter++;
  }
  while (myChar != 0);
}

void button_pressed() {
  byte butValue =  digitalRead(interruptPin);
  state = !state;
  Serial.println(butValue);
  CurrentDeck = random(0, NumberOfDecks);
  Serial.print("CurrentDeck: ");
  Serial.println(CurrentDeck);
}

void printRandomNote() {
  int counter = 0;
  int wordLength = 0;
  int myChar = 0;
  char word[150];

  int deckSize = getSize(AnkiDecks[CurrentDeck]);
  Serial.print("deckSize size: "); Serial.println(deckSize);
  int randomIndexInDeck = random(0, deckSize);
  Serial.print("random deck index: ");  Serial.println(randomIndexInDeck);
  counter = randomIndexInDeck;
  do {
    myChar =  pgm_read_byte_near(AnkiDecks[CurrentDeck] + counter);
    counter--;
  }
  while (myChar != 13);
  counter = counter + 2;
  do {
    myChar =  pgm_read_byte_near(AnkiDecks[CurrentDeck] + counter);
    word[wordLength] = (char) myChar;
    wordLength++;
    counter++;
  }
  while (myChar != 13);

  Serial.println(word);
  ShowCard(word);
  memset(word, 0, sizeof(word));
}

void ShowCard(String card) {
  //Adafruit_SSD1306 display(-1); // NodeMCU | !IMPORTANT
  Adafruit_SSD1306 display(4); // NANO
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.println(card);

  // Output the index of the deck as a debug message:
  display.setTextSize(1);
  display.setCursor(116, 25); //Width=128(real = 116), Height=64(real=25)
  display.print(CurrentDeck);

  display.display();
  delay(1);
}
