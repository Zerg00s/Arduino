const char longText[] PROGMEM = {"avid\rhackneyed\rmundane\rcompulsive \rcorny\rcliffhanger\ratrocious \rtopical\rcontrived\rtake it or leave it\rgritty\roff the mark \rgo round the houses\rdone and dusted\rtake a chill pill\rsleep on it\rdeceased\ra dirt road\rdraw up\rsiding (a)\rdare sb to do sth\rstoker\rto toss (sb sth)\rtin\runattainable\rthrashing\rclutterd with sth\ra thornbill\ra molope\rto wail\rcherished\rfuzzy\rhaunting\rtraumatic\rlingering\rfleeting\rrekindle a memory\rpush sth aside\rstir memories/emotions\rtrigger a memory\rconjure sth up\rblock sth out\rblot sth out\rblow your own trumpet\rtentative\revocative\rat the crack of dawn\rto hedge \rhedge your bets\rbeat sb fair and square\rsangfroid\rto feign\rto gloat\rfreak\rdismal\ra sash window\runfazed (by)\rportly\rlike a top\ra bowler hat\rpin-striped\rcareworn\rbode well/ill\rmorosely\rruckus\rto savour\rto scheme\rself-proclaimed\rget wind of\rencompass\rdumbstruck\rit's odds on\rlive and let live\rhoax\ra gerbil\rto bleat\rto chortle\rgruelling\rdismay\rChancellor of the Exchequer\rto prise\rsopping wet\rAxminster\rto rant\rfill somebody in\rto fill in time\rfill in for somebody\ramber\rharrassed\rto splutter\rhoarsely\rflustered\rfretful\rto grope\rcast about\rstab of fear\rto eclipse\rto smug\r(a) dip\ra combo\ra lust\rto lust after\rservitude\rto flog\reerie\rthrust \rto tap (into)\rdistil / distill\rbe/look old hat\rto draw (with)\rto draw on/upon sth\ra mound\rto swipe\rto tickle sb into\ra knuckle\rto rap/a rap\ra rap on\ranew\rcentre on/upon something\ra dweeb\rdreary\rludicrous, ludicrously \rlovable / loveable\ra lunk (slang)\rto nip\rfinesse / to finesse\rbe part and parcel of something\ra touch\rto thump\rfruition (formal)\ra dystopia \rgroundbreaking\rfestive\rhooked (informal)\rsurreptitiously\roverstatement\rtwirl\rhavoc\rwreak (to)\rGood greif!\rrigging\rto colour (up)\rto cave in to sth\ratrocity plural atrocities\rto elude\rto stamp\ran ice bucket \rto uproot\rto grimace\rto baffle\rhave a field day (informal)\rleft, right, and centre\rOnce upon a happier time \rdawning horror\rto swoop\rweak-kneed\rattempt AT (doing) sth\rAT the first/second attempt\rshrunken\rto budge\raggrieved\rto flinch\ra grate\rstreaks\ra mane\rtawny\rrangy\rshrewd\ra keyhole\ra lookout\ra flicker of\raddle brains\rrear (up)\rscrawny\rwary\rlose one's bearings\ra quarry\rrailing\rdilapidation\rdunghill\rto snarl\radmonitory\rto board up\rstrained\rthreadbare\rrickety\rvermin\rhunchback\rto simper/ a simper\rto caress\rto wince\rto crave\rto scurry\rto glower\rto discompose\rto hoodwink\rdiscomfit\rforestall\ra stint\ra stooge\rto thwart sb\rto inflect\rto apportion\rinvincible\rto dispose of\rto rally\rrally around\ra tight corner\robnoxious\rallegiance\rspin-spun-spun\rscathing\rtherein\rto seep\rdouse , dowse\rto jerk\rbe in on sth\rto stoop to\rto steer\rto slop\rcackle\ra windowpane\rfug\rshock (a)\rsmattering\rsmattering of\rhiggledy-piggledy\rtangled (up)\rblare (out)\rfabled\rhitherto\rrife\rctd. \rravage\rrift\rreinstate\rto surface\rstringent\rarray\rtask force\rto survey\rto swivel\rresidue\rtrespass (a) \ra stand\rto coat\rto masquerade\ra squad\rbreadcrumbs\rto/of no avail\rlopsided\rto slant\rto furl\ra missive\rto shrug sth off\rto go astray\rto lead sb astray\rto billow\rto lob\rpanicky\rto clamber\rto wrench\remblazoned\rto allot\rallotment\r\0"};
//32 10 13 == " \n\r" == SPACE,  Line feed (LF),  Carriage return (CR)

// Then set up a table to refer to your strings.

void setup()
{
  // PSTR (" Program Memory String ") <- inline FLASH string variable
  Serial.begin(9600);
  while(!Serial); // wait for serial port to connect. Needed for native USB
  Serial.println("OK");
}

void loop()
{ 
  printMessage();
  delay(3000);    
}

void printMessage() {
  int counter = 0;
  int wordLength = 0;
  int myChar=0;
  char word[150];  
  do {
    myChar =  pgm_read_byte_near(longText + counter);    
    if (myChar == 0){
      return;
    }
    
    if(myChar != 13){
      word[wordLength] = (char) myChar;
      wordLength++;
    }
    else{
      Serial.println(word);
      memset(word, 0, sizeof(word));
      wordLength = 0;
      delay(300); // new word begins      
    }      
       
    counter++;
  } 
  while (myChar != 0);
  }