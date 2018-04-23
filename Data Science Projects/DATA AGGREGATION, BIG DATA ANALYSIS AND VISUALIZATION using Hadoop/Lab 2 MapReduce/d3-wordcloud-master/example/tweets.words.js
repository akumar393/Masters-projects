// word frequencies of first two chapters of Oliver Twist
var words_tweets = [
    {
        "size": 15660,
        "text": "rt"
    },
    {
        "size": 13541,
        "text": "immigration"
    },
    {
        "size": 2569,
        "text": "trump"
    },
    {
        "size": 1551,
        "text": "new"
    },
    {
        "size": 1315,
        "text": "immigrants"
    },
    {
        "size": 1294,
        "text": "daca"
    },
    {
        "size": 1182,
        "text": "come"
    },
    {
        "size": 1141,
        "text": "democrats"
    },
    {
        "size": 1139,
        "text": "mexico"
    },
    {
        "size": 1098,
        "text": "realdonaldtrump"
    },
    {
        "size": 1053,
        "text": "welfare"
    },
    {
        "size": 1052,
        "text": "raise"
    },
    {
        "size": 1046,
        "text": "whats"
    },
    {
        "size": 1044,
        "text": "taxes"
    },
    {
        "size": 1038,
        "text": "platform"
    },
    {
        "size": 990,
        "text": "policy"
    },
    {
        "size": 985,
        "text": "sandratxas"
    },
    {
        "size": 973,
        "text": "brexit"
    },
    {
        "size": 881,
        "text": "uk"
    },
    {
        "size": 848,
        "text": "border"
    },
    {
        "size": 816,
        "text": "problem"
    },
    {
        "size": 814,
        "text": "people"
    },
    {
        "size": 725,
        "text": "girl4_trump"
    },
    {
        "size": 725,
        "text": "regulation"
    },
    {
        "size": 681,
        "text": "send"
    },
    {
        "size": 677,
        "text": "military"
    },
    {
        "size": 676,
        "text": "caravan"
    },
    {
        "size": 666,
        "text": "central"
    },
    {
        "size": 646,
        "text": "americans"
    },
    {
        "size": 643,
        "text": "stop"
    },
    {
        "size": 618,
        "text": "illegal"
    },
    {
        "size": 599,
        "text": "ice"
    },
    {
        "size": 596,
        "text": "think"
    },
    {
        "size": 593,
        "text": "huge"
    },
    {
        "size": 584,
        "text": "does"
    },
    {
        "size": 570,
        "text": "davidleopold"
    },
    {
        "size": 555,
        "text": "obama"
    },
    {
        "size": 546,
        "text": "u"
    },
    {
        "size": 545,
        "text": "california"
    },
    {
        "size": 539,
        "text": "headed"
    },
    {
        "size": 537,
        "text": "elderly"
    },
    {
        "size": 525,
        "text": "muslim"
    },
    {
        "size": 524,
        "text": "city"
    },
    {
        "size": 520,
        "text": "children"
    },
    {
        "size": 508,
        "text": "answer"
    },
    {
        "size": 507,
        "text": "women"
    },
    {
        "size": 506,
        "text": "pregnant"
    },
    {
        "size": 505,
        "text": "france"
    },
    {
        "size": 504,
        "text": "london"
    },
    {
        "size": 503,
        "text": "like"
    },
    {
        "size": 493,
        "text": "britain"
    },
    {
        "size": 491,
        "text": "days"
    },
    {
        "size": 480,
        "text": "congress"
    },
    {
        "size": 476,
        "text": "twitter"
    },
    {
        "size": 474,
        "text": "citizenship"
    },
    {
        "size": 470,
        "text": "smartdissent"
    },
    {
        "size": 469,
        "text": "wants"
    },
    {
        "size": 468,
        "text": "detention"
    },
    {
        "size": 463,
        "text": "immigr\\u2026"
    },
    {
        "size": 460,
        "text": "crime"
    },
    {
        "size": 452,
        "text": "guncontrol"
    },
    {
        "size": 448,
        "text": "level"
    },
    {
        "size": 447,
        "text": "murders"
    },
    {
        "size": 446,
        "text": "killed"
    },
    {
        "size": 445,
        "text": "banned"
    },
    {
        "size": 445,
        "text": "sadiq"
    },
    {
        "size": 442,
        "text": "year"
    },
    {
        "size": 440,
        "text": "handguns"
    },
    {
        "size": 440,
        "text": "khan\\u2019s"
    },
    {
        "size": 439,
        "text": "golfinggary"
    },
    {
        "size": 439,
        "text": "holocaust"
    },
    {
        "size": 439,
        "text": "newyorkcity"
    },
    {
        "size": 438,
        "text": "complete"
    },
    {
        "size": 437,
        "text": "neighbor"
    },
    {
        "size": 435,
        "text": "knew"
    },
    {
        "size": 434,
        "text": "seven"
    },
    {
        "size": 434,
        "text": "survivor"
    },
    {
        "size": 430,
        "text": "just"
    },
    {
        "size": 422,
        "text": "america"
    },
    {
        "size": 420,
        "text": "government"
    },
    {
        "size": 418,
        "text": "ignorance"
    },
    {
        "size": 416,
        "text": "administration"
    },
    {
        "size": 410,
        "text": "daca"
    },
    {
        "size": 409,
        "text": "100"
    },
    {
        "size": 407,
        "text": "potus"
    },
    {
        "size": 404,
        "text": "fix"
    },
    {
        "size": 403,
        "text": "demonstrated"
    },
    {
        "size": 403,
        "text": "repgutierrez"
    },
    {
        "size": 401,
        "text": "immigrant"
    },
    {
        "size": 400,
        "text": "(again)"
    },
    {
        "size": 400,
        "text": "qualifies"
    },
    {
        "size": 392,
        "text": "farageonlbc"
    },
    {
        "size": 392,
        "text": "h1b"
    },
    {
        "size": 383,
        "text": "country"
    },
    {
        "size": 382,
        "text": "o\\u2026"
    },
    {
        "size": 380,
        "text": "\\\""
    },
    {
        "size": 380,
        "text": "hope"
    },
    {
        "size": 378,
        "text": "promised"
    },
    {
        "size": 377,
        "text": "visa"
    },
    {
        "size": 377,
        "text": "watch"
    },
    {
        "size": 376,
        "text": "fixed"
    },
    {
        "size": 376,
        "text": "immediately"
    },
    {
        "size": 375,
        "text": "he\\u2019d"
    },
    {
        "size": 374,
        "text": "policies"
    },
    {
        "size": 370,
        "text": "jamierodr10"
    },
    {
        "size": 367,
        "text": "need"
    },
    {
        "size": 360,
        "text": "canada"
    },
    {
        "size": 358,
        "text": "years"
    },
    {
        "size": 351,
        "text": "right"
    },
    {
        "size": 345,
        "text": "federal"
    },
    {
        "size": 345,
        "text": "islam"
    },
    {
        "size": 341,
        "text": "released"
    },
    {
        "size": 339,
        "text": "fraud"
    },
    {
        "size": 337,
        "text": "it's"
    },
    {
        "size": 333,
        "text": "court"
    },
    {
        "size": 333,
        "text": "republicans"
    },
    {
        "size": 328,
        "text": "gotta"
    },
    {
        "size": 327,
        "text": "\\u201cyou"
    },
    {
        "size": 327,
        "text": "russia"
    },
    {
        "size": 326,
        "text": "adios\\ud83d\\udc4b\\ud83c\\udffc\\ud83d\\udc4b\\ud83c\\udffc"
    },
    {
        "size": 326,
        "text": "back\\u201d"
    },
    {
        "size": 325,
        "text": "usahotlips"
    },
    {
        "size": 322,
        "text": "finalsay"
    },
    {
        "size": 321,
        "text": "terrorism"
    },
    {
        "size": 319,
        "text": "countries"
    },
    {
        "size": 316,
        "text": "says"
    },
    {
        "size": 313,
        "text": "claims"
    },
    {
        "size": 307,
        "text": "question"
    },
    {
        "size": 306,
        "text": "judges"
    },
    {
        "size": 305,
        "text": "brandongroeny"
    },
    {
        "size": 302,
        "text": "deportation"
    },
    {
        "size": 302,
        "text": "latest"
    },
    {
        "size": 302,
        "text": "raises"
    },
    {
        "size": 302,
        "text": "regulat\\u2026"
    },
    {
        "size": 301,
        "text": "irony"
    },
    {
        "size": 298,
        "text": "elect"
    },
    {
        "size": 297,
        "text": "2/piece"
    },
    {
        "size": 297,
        "text": "allegations"
    },
    {
        "size": 297,
        "text": "census"
    },
    {
        "size": 297,
        "text": "djt"
    },
    {
        "size": 296,
        "text": "screams"
    },
    {
        "size": 295,
        "text": "time"
    },
    {
        "size": 284,
        "text": "stopbrexit"
    },
    {
        "size": 283,
        "text": "law"
    },
    {
        "size": 282,
        "text": "report"
    },
    {
        "size": 282,
        "text": "visas"
    },
    {
        "size": 281,
        "text": "living"
    },
    {
        "size": 280,
        "text": "\\u27a1"
    },
    {
        "size": 279,
        "text": "biggest"
    },
    {
        "size": 279,
        "text": "immigration\\u2026"
    },
    {
        "size": 277,
        "text": "t\\u2026"
    },
    {
        "size": 275,
        "text": "s\\u2026"
    },
    {
        "size": 274,
        "text": "2018"
    },
    {
        "size": 274,
        "text": "know"
    },
    {
        "size": 273,
        "text": "deal"
    },
    {
        "size": 270,
        "text": "breaking"
    },
    {
        "size": 269,
        "text": "said"
    },
    {
        "size": 268,
        "text": "legal"
    },
    {
        "size": 266,
        "text": "dreamers"
    },
    {
        "size": 263,
        "text": "end"
    },
    {
        "size": 261,
        "text": "thr\\u2026"
    },
    {
        "size": 257,
        "text": "danmathewsbooks"
    },
    {
        "size": 257,
        "text": "decision"
    },
    {
        "size": 257,
        "text": "news"
    },
    {
        "size": 256,
        "text": "freedomofspeech"
    },
    {
        "size": 256,
        "text": "sanctuary"
    },
    {
        "size": 256,
        "text": "states"
    },
    {
        "size": 252,
        "text": "going"
    },
    {
        "size": 252,
        "text": "help"
    },
    {
        "size": 244,
        "text": "actions"
    },
    {
        "size": 243,
        "text": "sanctuarystate"
    },
    {
        "size": 239,
        "text": "want"
    },
    {
        "size": 237,
        "text": "\\u201d"
    },
    {
        "size": 235,
        "text": "growing"
    },
    {
        "size": 234,
        "text": "family"
    },
    {
        "size": 234,
        "text": "siia_us"
    },
    {
        "size": 231,
        "text": "trump's"
    },
    {
        "size": 231,
        "text": "working"
    },
    {
        "size": 230,
        "text": "great"
    },
    {
        "size": 229,
        "text": "eu"
    },
    {
        "size": 226,
        "text": "tomilahren"
    },
    {
        "size": 224,
        "text": "page"
    },
    {
        "size": 221,
        "text": "californians"
    },
    {
        "size": 220,
        "text": "china"
    },
    {
        "size": 220,
        "text": "communities"
    },
    {
        "size": 220,
        "text": "recently\\u00a0asked"
    },
    {
        "size": 220,
        "text": "topic"
    },
    {
        "size": 219,
        "text": "arizonakayte"
    },
    {
        "size": 217,
        "text": "presidenttrump"
    },
    {
        "size": 214,
        "text": "gop"
    },
    {
        "size": 213,
        "text": "laws"
    },
    {
        "size": 213,
        "text": "read"
    },
    {
        "size": 213,
        "text": "|"
    },
    {
        "size": 211,
        "text": "allow"
    },
    {
        "size": 209,
        "text": "week"
    },
    {
        "size": 208,
        "text": "sorted"
    },
    {
        "size": 208,
        "text": "wall"
    },
    {
        "size": 204,
        "text": "consulting"
    },
    {
        "size": 204,
        "text": "life"
    },
    {
        "size": 204,
        "text": "undocumented"
    },
    {
        "size": 204,
        "text": "w\\u2026"
    },
    {
        "size": 204,
        "text": "young"
    },
    {
        "size": 203,
        "text": "tracking"
    },
    {
        "size": 202,
        "text": "database"
    },
    {
        "size": 201,
        "text": "state"
    },
    {
        "size": 200,
        "text": "foxnews\\u2026"
    },
    {
        "size": 200,
        "text": "migrants"
    },
    {
        "size": 199,
        "text": "false"
    },
    {
        "size": 198,
        "text": "abrupt"
    },
    {
        "size": 198,
        "text": "boris_sanchez"
    },
    {
        "size": 198,
        "text": "brexitukreality"
    },
    {
        "size": 198,
        "text": "case"
    },
    {
        "size": 198,
        "text": "making"
    },
    {
        "size": 198,
        "text": "outfrontcnn"
    },
    {
        "size": 197,
        "text": "continued"
    },
    {
        "size": 197,
        "text": "emolclause"
    },
    {
        "size": 197,
        "text": "job"
    },
    {
        "size": 197,
        "text": "mass"
    },
    {
        "size": 196,
        "text": "disgusting"
    },
    {
        "size": 196,
        "text": "old"
    },
    {
        "size": 195,
        "text": "looking"
    },
    {
        "size": 195,
        "text": "march"
    },
    {
        "size": 195,
        "text": "national"
    },
    {
        "size": 195,
        "text": "questions"
    },
    {
        "size": 195,
        "text": "ready"
    },
    {
        "size": 194,
        "text": "fear"
    },
    {
        "size": 194,
        "text": "today"
    },
    {
        "size": 194,
        "text": "work"
    },
    {
        "size": 192,
        "text": "clinton"
    },
    {
        "size": 192,
        "text": "infecting"
    },
    {
        "size": 192,
        "text": "knows"
    },
    {
        "size": 192,
        "text": "perpetuates"
    },
    {
        "size": 192,
        "text": "workers"
    },
    {
        "size": 191,
        "text": "population"
    },
    {
        "size": 191,
        "text": "support"
    },
    {
        "size": 191,
        "text": "winning"
    },
    {
        "size": 190,
        "text": "repmikequigley"
    },
    {
        "size": 190,
        "text": "sele\\u2026"
    },
    {
        "size": 190,
        "text": "success"
    },
    {
        "size": 189,
        "text": "study"
    },
    {
        "size": 184,
        "text": "place"
    },
    {
        "size": 184,
        "text": "vs"
    },
    {
        "size": 182,
        "text": "surprised"
    },
    {
        "size": 181,
        "text": "attempts"
    },
    {
        "size": 181,
        "text": "group"
    },
    {
        "size": 181,
        "text": "lawyers"
    },
    {
        "size": 181,
        "text": "students"
    },
    {
        "size": 181,
        "text": "undermine"
    },
    {
        "size": 180,
        "text": "5"
    },
    {
        "size": 180,
        "text": "blinks"
    },
    {
        "size": 180,
        "text": "needs"
    },
    {
        "size": 180,
        "text": "pathetic"
    },
    {
        "size": 180,
        "text": "rinos"
    },
    {
        "size": 180,
        "text": "spite"
    },
    {
        "size": 179,
        "text": "day"
    },
    {
        "size": 179,
        "text": "fakenews\\u2026"
    },
    {
        "size": 179,
        "text": "libturds"
    },
    {
        "size": 179,
        "text": "wattsjim"
    },
    {
        "size": 178,
        "text": "data"
    },
    {
        "size": 178,
        "text": "let"
    },
    {
        "size": 177,
        "text": "coming"
    },
    {
        "size": 177,
        "text": "doing"
    },
    {
        "size": 176,
        "text": "texas"
    },
    {
        "size": 176,
        "text": "thread"
    },
    {
        "size": 175,
        "text": "ckuck"
    },
    {
        "size": 174,
        "text": "12"
    },
    {
        "size": 174,
        "text": "ailanational"
    },
    {
        "size": 174,
        "text": "quotas"
    },
    {
        "size": 174,
        "text": "start"
    },
    {
        "size": 173,
        "text": "migration"
    },
    {
        "size": 173,
        "text": "parents"
    },
    {
        "size": 172,
        "text": "free"
    },
    {
        "size": 171,
        "text": "refugees"
    },
    {
        "size": 170,
        "text": "american"
    },
    {
        "size": 170,
        "text": "anirb_das"
    },
    {
        "size": 170,
        "text": "human"
    },
    {
        "size": 169,
        "text": "co/7i88fekcce"
    },
    {
        "size": 169,
        "text": "factsmatter"
    },
    {
        "size": 169,
        "text": "families"
    },
    {
        "size": 168,
        "text": "admin"
    },
    {
        "size": 166,
        "text": "care"
    },
    {
        "size": 166,
        "text": "maga"
    },
    {
        "size": 165,
        "text": "complex"
    },
    {
        "size": 163,
        "text": "dems"
    },
    {
        "size": 163,
        "text": "president"
    },
    {
        "size": 162,
        "text": "story"
    },
    {
        "size": 161,
        "text": "what's"
    },
    {
        "size": 159,
        "text": "deported"
    },
    {
        "size": 159,
        "text": "workforce"
    },
    {
        "size": 158,
        "text": "make"
    },
    {
        "size": 158,
        "text": "the\\u2026"
    },
    {
        "size": 157,
        "text": "40"
    },
    {
        "size": 157,
        "text": "event"
    },
    {
        "size": 156,
        "text": "cases"
    },
    {
        "size": 156,
        "text": "health"
    },
    {
        "size": 156,
        "text": "honduras"
    },
    {
        "size": 156,
        "text": "miguna"
    },
    {
        "size": 155,
        "text": "13"
    },
    {
        "size": 154,
        "text": "controls"
    },
    {
        "size": 154,
        "text": "deportation\\u2026"
    },
    {
        "size": 154,
        "text": "easter"
    },
    {
        "size": 153,
        "text": "crossings"
    },
    {
        "size": 153,
        "text": "world"
    },
    {
        "size": 152,
        "text": "buildthewall"
    },
    {
        "size": 152,
        "text": "status"
    },
    {
        "size": 150,
        "text": "county"
    },
    {
        "size": 150,
        "text": "gun"
    },
    {
        "size": 150,
        "text": "statements"
    },
    {
        "size": 149,
        "text": "fastest"
    },
    {
        "size": 149,
        "text": "goes"
    },
    {
        "size": 149,
        "text": "lowest"
    },
    {
        "size": 149,
        "text": "trump\\u2019s"
    },
    {
        "size": 148,
        "text": "thank"
    },
    {
        "size": 148,
        "text": "we're"
    },
    {
        "size": 147,
        "text": "1970s;"
    },
    {
        "size": 147,
        "text": "alt_uscis"
    },
    {
        "size": 147,
        "text": "committee"
    },
    {
        "size": 147,
        "text": "joseiswriting"
    },
    {
        "size": 147,
        "text": "leave"
    },
    {
        "size": 147,
        "text": "weak"
    },
    {
        "size": 145,
        "text": "according"
    },
    {
        "size": 145,
        "text": "undocument\\u2026"
    },
    {
        "size": 144,
        "text": "doesn't"
    },
    {
        "size": 143,
        "text": "student"
    },
    {
        "size": 142,
        "text": "usa"
    },
    {
        "size": 140,
        "text": "cities"
    },
    {
        "size": 139,
        "text": "busy"
    },
    {
        "size": 139,
        "text": "diverse"
    },
    {
        "size": 138,
        "text": "corporations"
    },
    {
        "size": 138,
        "text": "rubyrockstar333"
    },
    {
        "size": 137,
        "text": "clear"
    },
    {
        "size": 137,
        "text": "conscious"
    },
    {
        "size": 137,
        "text": "far"
    },
    {
        "size": 137,
        "text": "johnzimmer"
    },
    {
        "size": 137,
        "text": "lyft"
    },
    {
        "size": 137,
        "text": "socially"
    },
    {
        "size": 137,
        "text": "thing"
    },
    {
        "size": 137,
        "text": "united"
    },
    {
        "size": 136,
        "text": "aprildryan"
    },
    {
        "size": 135,
        "text": "don't"
    },
    {
        "size": 135,
        "text": "happening"
    },
    {
        "size": 135,
        "text": "india"
    },
    {
        "size": 135,
        "text": "worked"
    },
    {
        "size": 134,
        "text": "thanks"
    },
    {
        "size": 133,
        "text": "attorney"
    },
    {
        "size": 133,
        "text": "better"
    },
    {
        "size": 133,
        "text": "change"
    },
    {
        "size": 133,
        "text": "putin"
    },
    {
        "size": 133,
        "text": "storm\\u2026"
    },
    {
        "size": 132,
        "text": "based"
    },
    {
        "size": 132,
        "text": "i\\u2026"
    },
    {
        "size": 131,
        "text": "having"
    },
    {
        "size": 130,
        "text": "courts"
    },
    {
        "size": 130,
        "text": "public"
    },
    {
        "size": 130,
        "text": "published"
    },
    {
        "size": 129,
        "text": "discuss"
    },
    {
        "size": 129,
        "text": "enforce"
    },
    {
        "size": 129,
        "text": "response"
    },
    {
        "size": 128,
        "text": "(and"
    },
    {
        "size": 128,
        "text": "h\\u2026"
    },
    {
        "size": 128,
        "text": "immigrati\\u2026"
    },
    {
        "size": 128,
        "text": "means"
    },
    {
        "size": 128,
        "text": "minister"
    },
    {
        "size": 128,
        "text": "nearly"
    },
    {
        "size": 127,
        "text": "crimmigration"
    },
    {
        "size": 127,
        "text": "lying"
    },
    {
        "size": 127,
        "text": "way"
    },
    {
        "size": 126,
        "text": "500"
    },
    {
        "size": 126,
        "text": "buil\\u2026"
    },
    {
        "size": 126,
        "text": "from\\u2026"
    },
    {
        "size": 126,
        "text": "international"
    },
    {
        "size": 125,
        "text": "suddenly"
    },
    {
        "size": 124,
        "text": "\\\"30"
    },
    {
        "size": 124,
        "text": "\\\"america"
    },
    {
        "size": 124,
        "text": "article"
    },
    {
        "size": 124,
        "text": "farageonlbc\\u2026"
    },
    {
        "size": 124,
        "text": "finalists"
    },
    {
        "size": 124,
        "text": "join"
    },
    {
        "size": 123,
        "text": "house"
    },
    {
        "size": 123,
        "text": "mexican"
    },
    {
        "size": 123,
        "text": "scienc\\u2026"
    },
    {
        "size": 122,
        "text": "hypocrisy"
    },
    {
        "size": 122,
        "text": "liberals"
    },
    {
        "size": 121,
        "text": "djlots3"
    },
    {
        "size": 121,
        "text": "home"
    },
    {
        "size": 121,
        "text": "scotland"
    },
    {
        "size": 121,
        "text": "securing"
    },
    {
        "size": 121,
        "text": "video"
    },
    {
        "size": 120,
        "text": "allthingztrump"
    },
    {
        "size": 120,
        "text": "buildthewallwithmilitaryfunds"
    },
    {
        "size": 120,
        "text": "co/bchvnuhif7"
    },
    {
        "size": 120,
        "text": "immi\\u2026"
    },
    {
        "size": 120,
        "text": "live"
    },
    {
        "size": 120,
        "text": "talking"
    },
    {
        "size": 120,
        "text": "understand"
    },
    {
        "size": 119,
        "text": "absolutely"
    },
    {
        "size": 119,
        "text": "campaigns"
    },
    {
        "size": 119,
        "text": "enforcement"
    },
    {
        "size": 118,
        "text": "rules"
    },
    {
        "size": 117,
        "text": "agbecerra"
    },
    {
        "size": 117,
        "text": "attack"
    },
    {
        "size": 117,
        "text": "check"
    },
    {
        "size": 117,
        "text": "culture"
    },
    {
        "size": 116,
        "text": "disgraceful"
    },
    {
        "size": 116,
        "text": "getting"
    },
    {
        "size": 116,
        "text": "high"
    },
    {
        "size": 116,
        "text": "i'm"
    },
    {
        "size": 116,
        "text": "officials"
    },
    {
        "size": 116,
        "text": "political"
    },
    {
        "size": 116,
        "text": "taking"
    },
    {
        "size": 115,
        "text": "australia"
    },
    {
        "size": 115,
        "text": "borders"
    },
    {
        "size": 115,
        "text": "chair"
    },
    {
        "size": 115,
        "text": "deportations"
    },
    {
        "size": 114,
        "text": "approx"
    },
    {
        "size": 114,
        "text": "growing)"
    },
    {
        "size": 114,
        "text": "racist"
    },
    {
        "size": 113,
        "text": "issue"
    },
    {
        "size": 113,
        "text": "onwithlogic"
    },
    {
        "size": 113,
        "text": "skilled"
    },
    {
        "size": 112,
        "text": "illegals"
    },
    {
        "size": 112,
        "text": "look"
    },
    {
        "size": 112,
        "text": "travel"
    },
    {
        "size": 111,
        "text": "centralamericans"
    },
    {
        "size": 111,
        "text": "foreign"
    },
    {
        "size": 111,
        "text": "really"
    },
    {
        "size": 110,
        "text": "1)"
    },
    {
        "size": 110,
        "text": "falseflag"
    },
    {
        "size": 110,
        "text": "p\\u2026"
    },
    {
        "size": 109,
        "text": "april"
    },
    {
        "size": 109,
        "text": "select"
    },
    {
        "size": 108,
        "text": "americasvoice"
    },
    {
        "size": 108,
        "text": "enforcing"
    },
    {
        "size": 107,
        "text": "//t\\u2026"
    },
    {
        "size": 107,
        "text": "age"
    },
    {
        "size": 107,
        "text": "dealing"
    },
    {
        "size": 107,
        "text": "devolving"
    },
    {
        "size": 107,
        "text": "hate"
    },
    {
        "size": 107,
        "text": "jamiejkerr"
    },
    {
        "size": 107,
        "text": "prisons"
    },
    {
        "size": 106,
        "text": "coerce"
    },
    {
        "size": 106,
        "text": "good"
    },
    {
        "size": 106,
        "text": "govt's"
    },
    {
        "size": 106,
        "text": "happen"
    },
    {
        "size": 106,
        "text": "trade"
    },
    {
        "size": 105,
        "text": "community"
    },
    {
        "size": 105,
        "text": "doesn\\u2019t"
    },
    {
        "size": 105,
        "text": "reform"
    },
    {
        "size": 104,
        "text": "act"
    },
    {
        "size": 104,
        "text": "current"
    },
    {
        "size": 104,
        "text": "hungary"
    },
    {
        "size": 104,
        "text": "important"
    },
    {
        "size": 104,
        "text": "proud"
    },
    {
        "size": 104,
        "text": "social"
    },
    {
        "size": 104,
        "text": "things"
    },
    {
        "size": 104,
        "text": "veteran"
    },
    {
        "size": 104,
        "text": "you're"
    },
    {
        "size": 102,
        "text": "department"
    },
    {
        "size": 102,
        "text": "issues"
    },
    {
        "size": 102,
        "text": "left"
    },
    {
        "size": 101,
        "text": "("
    },
    {
        "size": 101,
        "text": "4"
    },
    {
        "size": 100,
        "text": "he\\u2019s"
    },
    {
        "size": 100,
        "text": "immigrants\\u2026"
    },
    {
        "size": 100,
        "text": "politics"
    },
    {
        "size": 99,
        "text": "finalsay\\u2026"
    },
    {
        "size": 99,
        "text": "gates"
    },
    {
        "size": 99,
        "text": "majority"
    },
    {
        "size": 99,
        "text": "real"
    },
    {
        "size": 99,
        "text": "stormydaniels"
    },
    {
        "size": 99,
        "text": "th\\u2026"
    },
    {
        "size": 99,
        "text": "told"
    },
    {
        "size": 99,
        "text": "truth"
    },
    {
        "size": 98,
        "text": "attacks"
    },
    {
        "size": 98,
        "text": "discussion"
    },
    {
        "size": 98,
        "text": "flynn"
    },
    {
        "size": 98,
        "text": "indians"
    },
    {
        "size": 98,
        "text": "lawsuit"
    },
    {
        "size": 98,
        "text": "process"
    },
    {
        "size": 97,
        "text": "bringing"
    },
    {
        "size": 97,
        "text": "century"
    },
    {
        "size": 97,
        "text": "citizens"
    },
    {
        "size": 97,
        "text": "european"
    },
    {
        "size": 97,
        "text": "universal"
    },
    {
        "size": 96,
        "text": "anti"
    },
    {
        "size": 96,
        "text": "secureourborders"
    },
    {
        "size": 96,
        "text": "white"
    },
    {
        "size": 95,
        "text": "20"
    },
    {
        "size": 95,
        "text": "in\\u2026"
    },
    {
        "size": 95,
        "text": "to\\u2026"
    },
    {
        "size": 95,
        "text": "using"
    },
    {
        "size": 95,
        "text": "worth"
    },
    {
        "size": 94,
        "text": "electionlawctr"
    },
    {
        "size": 94,
        "text": "gaypatriot"
    },
    {
        "size": 94,
        "text": "justice"
    },
    {
        "size": 94,
        "text": "lastweektonight"
    },
    {
        "size": 94,
        "text": "man"
    },
    {
        "size": 94,
        "text": "talk"
    },
    {
        "size": 93,
        "text": "cost"
    },
    {
        "size": 93,
        "text": "exactly"
    },
    {
        "size": 93,
        "text": "falling"
    },
    {
        "size": 93,
        "text": "say"
    },
    {
        "size": 92,
        "text": "labor"
    },
    {
        "size": 92,
        "text": "migrant"
    },
    {
        "size": 92,
        "text": "rights"
    },
    {
        "size": 91,
        "text": "alertenemy221b"
    },
    {
        "size": 91,
        "text": "asylum"
    },
    {
        "size": 91,
        "text": "refugee"
    },
    {
        "size": 91,
        "text": "southern"
    },
    {
        "size": 91,
        "text": "uscis"
    },
    {
        "size": 90,
        "text": "700"
    },
    {
        "size": 90,
        "text": "agriculture"
    },
    {
        "size": 90,
        "text": "europe"
    },
    {
        "size": 90,
        "text": "male"
    },
    {
        "size": 90,
        "text": "recent"
    },
    {
        "size": 90,
        "text": "shows"
    },
    {
        "size": 89,
        "text": "gc"
    },
    {
        "size": 89,
        "text": "largest"
    },
    {
        "size": 89,
        "text": "pathway"
    },
    {
        "size": 89,
        "text": "sex"
    },
    {
        "size": 89,
        "text": "voted"
    },
    {
        "size": 88,
        "text": "facebook"
    },
    {
        "size": 88,
        "text": "passover"
    },
    {
        "size": 88,
        "text": "sectors"
    },
    {
        "size": 88,
        "text": "trying"
    },
    {
        "size": 87,
        "text": "advocacy"
    },
    {
        "size": 87,
        "text": "away"
    },
    {
        "size": 87,
        "text": "fact"
    },
    {
        "size": 87,
        "text": "january"
    },
    {
        "size": 87,
        "text": "nafta"
    },
    {
        "size": 87,
        "text": "sessions"
    },
    {
        "size": 86,
        "text": "ca"
    },
    {
        "size": 86,
        "text": "certain"
    },
    {
        "size": 86,
        "text": "changed"
    },
    {
        "size": 86,
        "text": "joke"
    },
    {
        "size": 86,
        "text": "pro"
    },
    {
        "size": 86,
        "text": "turned"
    },
    {
        "size": 85,
        "text": "media"
    },
    {
        "size": 85,
        "text": "wanted"
    },
    {
        "size": 84,
        "text": "\\u2014"
    },
    {
        "size": 84,
        "text": "dr_philippaw"
    },
    {
        "size": 84,
        "text": "lawyer"
    },
    {
        "size": 84,
        "text": "scotland\\u2019s"
    },
    {
        "size": 84,
        "text": "security"
    },
    {
        "size": 84,
        "text": "service"
    },
    {
        "size": 84,
        "text": "set"
    },
    {
        "size": 83,
        "text": "agents"
    },
    {
        "size": 83,
        "text": "c\\u2026"
    },
    {
        "size": 83,
        "text": "do\\u2026"
    },
    {
        "size": 83,
        "text": "economic"
    },
    {
        "size": 83,
        "text": "st\\u2026"
    },
    {
        "size": 83,
        "text": "until\\u2026"
    },
    {
        "size": 83,
        "text": "you\\u2019re"
    },
    {
        "size": 82,
        "text": "\\\"the"
    },
    {
        "size": 82,
        "text": "makes"
    },
    {
        "size": 82,
        "text": "number"
    },
    {
        "size": 82,
        "text": "spouse"
    },
    {
        "size": 82,
        "text": "tell"
    },
    {
        "size": 81,
        "text": "daily"
    },
    {
        "size": 81,
        "text": "dropped"
    },
    {
        "size": 81,
        "text": "newsandguts"
    },
    {
        "size": 81,
        "text": "vote"
    },
    {
        "size": 80,
        "text": "10"
    },
    {
        "size": 80,
        "text": "enrollment"
    },
    {
        "size": 80,
        "text": "f\\u2026"
    },
    {
        "size": 80,
        "text": "kicking"
    },
    {
        "size": 79,
        "text": "applyin\\u2026"
    },
    {
        "size": 79,
        "text": "brexshittrade"
    },
    {
        "size": 79,
        "text": "business"
    },
    {
        "size": 79,
        "text": "crowd"
    },
    {
        "size": 79,
        "text": "program"
    },
    {
        "size": 79,
        "text": "quick"
    },
    {
        "size": 79,
        "text": "services"
    },
    {
        "size": 78,
        "text": "adult"
    },
    {
        "size": 78,
        "text": "ask"
    },
    {
        "size": 78,
        "text": "housing"
    },
    {
        "size": 78,
        "text": "jkia"
    },
    {
        "size": 78,
        "text": "morning"
    },
    {
        "size": 78,
        "text": "relies"
    },
    {
        "size": 77,
        "text": "close"
    },
    {
        "size": 77,
        "text": "estimates"
    },
    {
        "size": 77,
        "text": "foxnews"
    },
    {
        "size": 77,
        "text": "invasion"
    },
    {
        "size": 77,
        "text": "use"
    },
    {
        "size": 77,
        "text": "visit"
    },
    {
        "size": 77,
        "text": "yesterday"
    },
    {
        "size": 76,
        "text": "afraid"
    },
    {
        "size": 76,
        "text": "bans"
    },
    {
        "size": 76,
        "text": "brought"
    },
    {
        "size": 76,
        "text": "canadian"
    },
    {
        "size": 76,
        "text": "known"
    },
    {
        "size": 76,
        "text": "learn"
    },
    {
        "size": 76,
        "text": "stance"
    },
    {
        "size": 75,
        "text": "co/pnjqfihvat"
    },
    {
        "size": 75,
        "text": "danielgriswold"
    },
    {
        "size": 75,
        "text": "hard"
    },
    {
        "size": 75,
        "text": "keeping"
    },
    {
        "size": 75,
        "text": "kids"
    },
    {
        "size": 75,
        "text": "mercatus"
    },
    {
        "size": 75,
        "text": "noting"
    },
    {
        "size": 75,
        "text": "planning"
    },
    {
        "size": 75,
        "text": "preview"
    },
    {
        "size": 75,
        "text": "providing"
    },
    {
        "size": 74,
        "text": "1790"
    },
    {
        "size": 74,
        "text": "2a"
    },
    {
        "size": 74,
        "text": "big"
    },
    {
        "size": 74,
        "text": "int\\u2026"
    },
    {
        "size": 74,
        "text": "million"
    },
    {
        "size": 74,
        "text": "nytimes"
    },
    {
        "size": 74,
        "text": "repespaillat"
    },
    {
        "size": 74,
        "text": "share"
    },
    {
        "size": 74,
        "text": "suzannaowiyo"
    },
    {
        "size": 73,
        "text": "added"
    },
    {
        "size": 73,
        "text": "ago"
    },
    {
        "size": 73,
        "text": "and\\u2026"
    },
    {
        "size": 73,
        "text": "cultures"
    },
    {
        "size": 73,
        "text": "director"
    },
    {
        "size": 73,
        "text": "happy"
    },
    {
        "size": 73,
        "text": "it\\u2019s"
    },
    {
        "size": 73,
        "text": "nyc_erik"
    },
    {
        "size": 73,
        "text": "power"
    },
    {
        "size": 73,
        "text": "there's"
    },
    {
        "size": 73,
        "text": "turning"
    },
    {
        "size": 72,
        "text": "era"
    },
    {
        "size": 72,
        "text": "hear"
    },
    {
        "size": 72,
        "text": "impact"
    },
    {
        "size": 72,
        "text": "patrol"
    },
    {
        "size": 72,
        "text": "quota"
    },
    {
        "size": 72,
        "text": "speed"
    },
    {
        "size": 72,
        "text": "woman"
    },
    {
        "size": 71,
        "text": "detaining"
    },
    {
        "size": 71,
        "text": "donaldtrump"
    },
    {
        "size": 71,
        "text": "long"
    },
    {
        "size": 71,
        "text": "non"
    },
    {
        "size": 71,
        "text": "plan"
    },
    {
        "size": 71,
        "text": "putting"
    },
    {
        "size": 71,
        "text": "surprise"
    },
    {
        "size": 71,
        "text": "takebackcontrol"
    },
    {
        "size": 71,
        "text": "uncertainty"
    },
    {
        "size": 70,
        "text": "\\u201cno"
    },
    {
        "size": 70,
        "text": "don\\u2019t"
    },
    {
        "size": 70,
        "text": "employers"
    },
    {
        "size": 70,
        "text": "ha\\u2026"
    },
    {
        "size": 70,
        "text": "haitians"
    },
    {
        "size": 70,
        "text": "names"
    },
    {
        "size": 70,
        "text": "points"
    },
    {
        "size": 70,
        "text": "room"
    },
    {
        "size": 69,
        "text": "4th"
    },
    {
        "size": 69,
        "text": "\\u201ctrump"
    },
    {
        "size": 69,
        "text": "aids"
    },
    {
        "size": 69,
        "text": "army"
    },
    {
        "size": 69,
        "text": "changes"
    },
    {
        "size": 69,
        "text": "disagree"
    },
    {
        "size": 69,
        "text": "facts"
    },
    {
        "size": 69,
        "text": "forced"
    },
    {
        "size": 69,
        "text": "is\\u2026"
    },
    {
        "size": 69,
        "text": "jobs"
    },
    {
        "size": 69,
        "text": "liberians"
    },
    {
        "size": 69,
        "text": "tomorrow"
    },
    {
        "size": 69,
        "text": "wee"
    },
    {
        "size": 68,
        "text": "afghanistan"
    },
    {
        "size": 68,
        "text": "argument"
    },
    {
        "size": 68,
        "text": "arrest"
    },
    {
        "size": 68,
        "text": "criminal"
    },
    {
        "size": 68,
        "text": "demographics"
    },
    {
        "size": 68,
        "text": "illeg\\u2026"
    },
    {
        "size": 68,
        "text": "katie"
    },
    {
        "size": 68,
        "text": "language"
    },
    {
        "size": 68,
        "text": "pornstars"
    },
    {
        "size": 68,
        "text": "small"
    },
    {
        "size": 68,
        "text": "smarmyspaniels"
    },
    {
        "size": 68,
        "text": "w/"
    },
    {
        "size": 68,
        "text": "wh\\u2026"
    },
    {
        "size": 67,
        "text": "2016"
    },
    {
        "size": 67,
        "text": "\\u201cdreamers\\u201d"
    },
    {
        "size": 67,
        "text": "deserves"
    },
    {
        "size": 67,
        "text": "impose"
    },
    {
        "size": 67,
        "text": "monday"
    },
    {
        "size": 67,
        "text": "pilaraymara"
    },
    {
        "size": 67,
        "text": "war"
    },
    {
        "size": 66,
        "text": "\\u2013"
    },
    {
        "size": 66,
        "text": "\\u2551\\u2026"
    },
    {
        "size": 66,
        "text": "announced"
    },
    {
        "size": 66,
        "text": "born"
    },
    {
        "size": 66,
        "text": "bring"
    },
    {
        "size": 66,
        "text": "calm"
    },
    {
        "size": 66,
        "text": "cnn"
    },
    {
        "size": 66,
        "text": "completely"
    },
    {
        "size": 66,
        "text": "election"
    },
    {
        "size": 66,
        "text": "history"
    },
    {
        "size": 66,
        "text": "hopkins"
    },
    {
        "size": 66,
        "text": "laureldavilacpa"
    },
    {
        "size": 66,
        "text": "lower"
    },
    {
        "size": 66,
        "text": "post"
    },
    {
        "size": 66,
        "text": "true"
    },
    {
        "size": 66,
        "text": "wages"
    },
    {
        "size": 65,
        "text": "a$$"
    },
    {
        "size": 65,
        "text": "add"
    },
    {
        "size": 65,
        "text": "census2020"
    },
    {
        "size": 65,
        "text": "invloved"
    },
    {
        "size": 65,
        "text": "lockthemallup"
    },
    {
        "size": 65,
        "text": "nation"
    },
    {
        "size": 65,
        "text": "push"
    },
    {
        "size": 65,
        "text": "redwaverising"
    },
    {
        "size": 65,
        "text": "romney4utah"
    },
    {
        "size": 64,
        "text": "co/m\\u2026"
    },
    {
        "size": 64,
        "text": "entry"
    },
    {
        "size": 64,
        "text": "factory"
    },
    {
        "size": 64,
        "text": "immigra\\u2026"
    },
    {
        "size": 64,
        "text": "including"
    },
    {
        "size": 64,
        "text": "jenn_027"
    },
    {
        "size": 64,
        "text": "kennedyforutah"
    },
    {
        "size": 64,
        "text": "m\\u2026"
    },
    {
        "size": 64,
        "text": "of\\u2026"
    },
    {
        "size": 64,
        "text": "served"
    },
    {
        "size": 64,
        "text": "tuesday"
    },
    {
        "size": 63,
        "text": "aliens"
    },
    {
        "size": 63,
        "text": "australian"
    },
    {
        "size": 63,
        "text": "begins"
    },
    {
        "size": 63,
        "text": "detentio\\u2026"
    },
    {
        "size": 63,
        "text": "example"
    },
    {
        "size": 63,
        "text": "late"
    },
    {
        "size": 63,
        "text": "let's"
    },
    {
        "size": 63,
        "text": "open"
    },
    {
        "size": 63,
        "text": "stand"
    },
    {
        "size": 62,
        "text": "face"
    },
    {
        "size": 62,
        "text": "myth"
    },
    {
        "size": 62,
        "text": "passed"
    },
    {
        "size": 62,
        "text": "politicalhedge"
    },
    {
        "size": 62,
        "text": "private"
    },
    {
        "size": 62,
        "text": "run"
    },
    {
        "size": 62,
        "text": "they're"
    },
    {
        "size": 61,
        "text": "ban"
    },
    {
        "size": 61,
        "text": "build"
    },
    {
        "size": 61,
        "text": "burden"
    },
    {
        "size": 61,
        "text": "called"
    },
    {
        "size": 61,
        "text": "economy"
    },
    {
        "size": 61,
        "text": "ev\\u2026"
    },
    {
        "size": 61,
        "text": "info"
    },
    {
        "size": 61,
        "text": "month"
    },
    {
        "size": 61,
        "text": "natasharesists"
    },
    {
        "size": 61,
        "text": "records"
    },
    {
        "size": 61,
        "text": "regime"
    },
    {
        "size": 61,
        "text": "wake"
    },
    {
        "size": 60,
        "text": "aflores"
    },
    {
        "size": 60,
        "text": "applications"
    },
    {
        "size": 60,
        "text": "english"
    },
    {
        "size": 60,
        "text": "hypocritical"
    },
    {
        "size": 60,
        "text": "icegov"
    },
    {
        "size": 60,
        "text": "immig\\u2026"
    },
    {
        "size": 60,
        "text": "point"
    },
    {
        "size": 60,
        "text": "short"
    },
    {
        "size": 59,
        "text": "11"
    },
    {
        "size": 59,
        "text": "bad"
    },
    {
        "size": 59,
        "text": "citizen"
    },
    {
        "size": 59,
        "text": "financial"
    },
    {
        "size": 59,
        "text": "http\\u2026"
    },
    {
        "size": 59,
        "text": "immigrationreform"
    },
    {
        "size": 59,
        "text": "mi\\u2026"
    },
    {
        "size": 59,
        "text": "miscarriages"
    },
    {
        "size": 59,
        "text": "mrdarwindarling"
    },
    {
        "size": 59,
        "text": "remember"
    },
    {
        "size": 59,
        "text": "roundtable"
    },
    {
        "size": 59,
        "text": "senate"
    },
    {
        "size": 59,
        "text": "shock"
    },
    {
        "size": 59,
        "text": "tejas_marine"
    },
    {
        "size": 59,
        "text": "temporary"
    },
    {
        "size": 58,
        "text": "bureau"
    },
    {
        "size": 58,
        "text": "correlation"
    },
    {
        "size": 58,
        "text": "download"
    },
    {
        "size": 58,
        "text": "enter"
    },
    {
        "size": 58,
        "text": "here's"
    },
    {
        "size": 58,
        "text": "highlighting"
    },
    {
        "size": 58,
        "text": "joaquincastrotx"
    },
    {
        "size": 58,
        "text": "link"
    },
    {
        "size": 58,
        "text": "natashabutterfi"
    },
    {
        "size": 58,
        "text": "office"
    },
    {
        "size": 58,
        "text": "protect"
    },
    {
        "size": 58,
        "text": "sandra"
    },
    {
        "size": 58,
        "text": "simply"
    },
    {
        "size": 58,
        "text": "steph93065"
    },
    {
        "size": 57,
        "text": "cap"
    },
    {
        "size": 57,
        "text": "criminals"
    },
    {
        "size": 57,
        "text": "got"
    },
    {
        "size": 57,
        "text": "kind"
    },
    {
        "size": 57,
        "text": "led"
    },
    {
        "size": 57,
        "text": "mean"
    },
    {
        "size": 57,
        "text": "nilc_org"
    },
    {
        "size": 57,
        "text": "proves"
    },
    {
        "size": 57,
        "text": "putinspuppet"
    },
    {
        "size": 57,
        "text": "safety"
    },
    {
        "size": 57,
        "text": "seeking"
    },
    {
        "size": 56,
        "text": "authorities"
    },
    {
        "size": 56,
        "text": "b\\u2026"
    },
    {
        "size": 56,
        "text": "book"
    },
    {
        "size": 56,
        "text": "dhsgov"
    },
    {
        "size": 56,
        "text": "effect"
    },
    {
        "size": 56,
        "text": "exclusive"
    },
    {
        "size": 56,
        "text": "filed"
    },
    {
        "size": 56,
        "text": "giving"
    },
    {
        "size": 56,
        "text": "gr8americanmvmt"
    },
    {
        "size": 56,
        "text": "jbmoorephoto"
    },
    {
        "size": 56,
        "text": "repjerrynadler"
    },
    {
        "size": 56,
        "text": "solution"
    },
    {
        "size": 56,
        "text": "survey"
    },
    {
        "size": 56,
        "text": "we\\u2026"
    },
    {
        "size": 56,
        "text": "ye\\u2026"
    },
    {
        "size": 55,
        "text": "26"
    },
    {
        "size": 55,
        "text": "average"
    },
    {
        "size": 55,
        "text": "center"
    },
    {
        "size": 55,
        "text": "comes"
    },
    {
        "size": 55,
        "text": "diversity"
    },
    {
        "size": 55,
        "text": "drive"
    },
    {
        "size": 55,
        "text": "fox"
    },
    {
        "size": 55,
        "text": "friday"
    },
    {
        "size": 55,
        "text": "germany"
    },
    {
        "size": 55,
        "text": "hungary_journal"
    },
    {
        "size": 55,
        "text": "judge"
    },
    {
        "size": 55,
        "text": "suicide"
    },
    {
        "size": 55,
        "text": "threat"
    },
    {
        "size": 55,
        "text": "welcome"
    },
    {
        "size": 54,
        "text": "6"
    },
    {
        "size": 54,
        "text": "borderwall"
    },
    {
        "size": 54,
        "text": "can't"
    },
    {
        "size": 54,
        "text": "control"
    },
    {
        "size": 54,
        "text": "en\\u2026"
    },
    {
        "size": 54,
        "text": "evidence"
    },
    {
        "size": 54,
        "text": "fight"
    },
    {
        "size": 54,
        "text": "greencard"
    },
    {
        "size": 54,
        "text": "icymi"
    },
    {
        "size": 54,
        "text": "importance"
    },
    {
        "size": 54,
        "text": "kills"
    },
    {
        "size": 54,
        "text": "misery"
    },
    {
        "size": 54,
        "text": "neil_ruiz"
    },
    {
        "size": 54,
        "text": "plans"
    },
    {
        "size": 54,
        "text": "proposed"
    },
    {
        "size": 54,
        "text": "tylerdiep"
    },
    {
        "size": 54,
        "text": "washington"
    },
    {
        "size": 54,
        "text": "ways"
    },
    {
        "size": 53,
        "text": "applicants"
    },
    {
        "size": 53,
        "text": "benefits"
    },
    {
        "size": 53,
        "text": "executive"
    },
    {
        "size": 53,
        "text": "interview"
    },
    {
        "size": 53,
        "text": "lose"
    },
    {
        "size": 53,
        "text": "member"
    },
    {
        "size": 53,
        "text": "susanpai"
    },
    {
        "size": 53,
        "text": "youtube"
    },
    {
        "size": 52,
        "text": "abuse"
    },
    {
        "size": 52,
        "text": "commits"
    },
    {
        "size": 52,
        "text": "confines"
    },
    {
        "size": 52,
        "text": "craryap"
    },
    {
        "size": 52,
        "text": "experience"
    },
    {
        "size": 52,
        "text": "healthcare"
    },
    {
        "size": 52,
        "text": "ireland"
    },
    {
        "size": 52,
        "text": "marshals"
    },
    {
        "size": 52,
        "text": "matter"
    },
    {
        "size": 52,
        "text": "order"
    },
    {
        "size": 52,
        "text": "release"
    },
    {
        "size": 52,
        "text": "sure"
    },
    {
        "size": 52,
        "text": "wonder"
    },
    {
        "size": 52,
        "text": "~34"
    },
    {
        "size": 51,
        "text": "(from"
    },
    {
        "size": 51,
        "text": "aila"
    },
    {
        "size": 51,
        "text": "candidate"
    },
    {
        "size": 51,
        "text": "commerce"
    },
    {
        "size": 51,
        "text": "different"
    },
    {
        "size": 51,
        "text": "donald"
    },
    {
        "size": 51,
        "text": "homeland"
    },
    {
        "size": 51,
        "text": "land"
    },
    {
        "size": 51,
        "text": "orangecounty"
    },
    {
        "size": 51,
        "text": "rule"
    },
    {
        "size": 51,
        "text": "sheriff"
    },
    {
        "size": 51,
        "text": "soon"
    },
    {
        "size": 51,
        "text": "total\\u2026"
    },
    {
        "size": 51,
        "text": "wrong"
    },
    {
        "size": 50,
        "text": "ap)"
    },
    {
        "size": 50,
        "text": "california\\u2019s"
    },
    {
        "size": 50,
        "text": "demand"
    },
    {
        "size": 50,
        "text": "men"
    },
    {
        "size": 50,
        "text": "mind"
    },
    {
        "size": 50,
        "text": "protection"
    },
    {
        "size": 50,
        "text": "violence"
    },
    {
        "size": 49,
        "text": "'sanctuary'"
    },
    {
        "size": 49,
        "text": "blog"
    },
    {
        "size": 49,
        "text": "british"
    },
    {
        "size": 49,
        "text": "co/gldd7lnjo2"
    },
    {
        "size": 49,
        "text": "dangerous"
    },
    {
        "size": 49,
        "text": "detain"
    },
    {
        "size": 49,
        "text": "faces"
    },
    {
        "size": 49,
        "text": "fair"
    },
    {
        "size": 49,
        "text": "h"
    },
    {
        "size": 49,
        "text": "marriage"
    },
    {
        "size": 49,
        "text": "pass"
    },
    {
        "size": 49,
        "text": "piece"
    },
    {
        "size": 49,
        "text": "thomas"
    },
    {
        "size": 49,
        "text": "towns"
    },
    {
        "size": 49,
        "text": "track"
    },
    {
        "size": 49,
        "text": "won't"
    },
    {
        "size": 49,
        "text": "york"
    },
    {
        "size": 48,
        "text": "(https"
    },
    {
        "size": 48,
        "text": ")"
    },
    {
        "size": 48,
        "text": "break"
    },
    {
        "size": 48,
        "text": "brick"
    },
    {
        "size": 48,
        "text": "continues"
    },
    {
        "size": 48,
        "text": "jeff"
    },
    {
        "size": 48,
        "text": "list"
    },
    {
        "size": 48,
        "text": "local"
    },
    {
        "size": 48,
        "text": "race"
    },
    {
        "size": 48,
        "text": "require"
    },
    {
        "size": 48,
        "text": "rewind"
    },
    {
        "size": 47,
        "text": "\\u274ctrump"
    },
    {
        "size": 47,
        "text": "at\\u2026"
    },
    {
        "size": 47,
        "text": "challenge"
    },
    {
        "size": 47,
        "text": "co/qigkfss94f"
    },
    {
        "size": 47,
        "text": "february"
    },
    {
        "size": 47,
        "text": "happens"
    },
    {
        "size": 47,
        "text": "idea"
    },
    {
        "size": 47,
        "text": "jjdancen1"
    },
    {
        "size": 47,
        "text": "joined"
    },
    {
        "size": 47,
        "text": "party"
    },
    {
        "size": 47,
        "text": "podcast"
    },
    {
        "size": 47,
        "text": "ronbrownstein"
    },
    {
        "size": 47,
        "text": "today's"
    },
    {
        "size": 46,
        "text": "buzzfeednews"
    },
    {
        "size": 46,
        "text": "child"
    },
    {
        "size": 46,
        "text": "daughter"
    },
    {
        "size": 46,
        "text": "detainee"
    },
    {
        "size": 46,
        "text": "john"
    },
    {
        "size": 46,
        "text": "naturalization"
    },
    {
        "size": 46,
        "text": "pay"
    },
    {
        "size": 45,
        "text": "9"
    },
    {
        "size": 45,
        "text": "\\u2551"
    },
    {
        "size": 45,
        "text": "\\ud83c\\uddfa\\ud83c\\uddf8"
    },
    {
        "size": 45,
        "text": "admits"
    },
    {
        "size": 45,
        "text": "attitudes"
    },
    {
        "size": 45,
        "text": "can\\u2019t"
    },
    {
        "size": 45,
        "text": "discussing"
    },
    {
        "size": 45,
        "text": "express"
    },
    {
        "size": 45,
        "text": "hell"
    },
    {
        "size": 45,
        "text": "hold"
    },
    {
        "size": 45,
        "text": "hutchens"
    },
    {
        "size": 45,
        "text": "images"
    },
    {
        "size": 45,
        "text": "increase"
    },
    {
        "size": 45,
        "text": "l\\u2026"
    },
    {
        "size": 45,
        "text": "melania"
    },
    {
        "size": 45,
        "text": "minutes"
    },
    {
        "size": 45,
        "text": "paris"
    },
    {
        "size": 45,
        "text": "placing"
    },
    {
        "size": 45,
        "text": "protects"
    },
    {
        "size": 45,
        "text": "rape"
    },
    {
        "size": 45,
        "text": "relax"
    },
    {
        "size": 45,
        "text": "romney"
    },
    {
        "size": 45,
        "text": "sorry"
    },
    {
        "size": 45,
        "text": "speaking"
    },
    {
        "size": 45,
        "text": "sweden"
    },
    {
        "size": 45,
        "text": "theresamay"
    },
    {
        "size": 45,
        "text": "trumpsamerica"
    },
    {
        "size": 45,
        "text": "tx"
    },
    {
        "size": 45,
        "text": "undetected"
    },
    {
        "size": 44,
        "text": "21st"
    },
    {
        "size": 44,
        "text": "actually"
    },
    {
        "size": 44,
        "text": "ahead"
    },
    {
        "size": 44,
        "text": "apply"
    },
    {
        "size": 44,
        "text": "caught"
    },
    {
        "size": 44,
        "text": "chil\\u2026"
    },
    {
        "size": 44,
        "text": "constitution"
    },
    {
        "size": 44,
        "text": "crimes"
    },
    {
        "size": 44,
        "text": "debate"
    },
    {
        "size": 44,
        "text": "deporting"
    },
    {
        "size": 44,
        "text": "ejinaction"
    },
    {
        "size": 44,
        "text": "experts"
    },
    {
        "size": 44,
        "text": "freetrade"
    },
    {
        "size": 44,
        "text": "held"
    },
    {
        "size": 44,
        "text": "im\\u2026"
    },
    {
        "size": 44,
        "text": "jennaneen"
    },
    {
        "size": 44,
        "text": "journey"
    },
    {
        "size": 44,
        "text": "named"
    },
    {
        "size": 44,
        "text": "nj"
    },
    {
        "size": 44,
        "text": "overstaying"
    },
    {
        "size": 44,
        "text": "record"
    },
    {
        "size": 44,
        "text": "yes"
    },
    {
        "size": 43,
        "text": "'the"
    },
    {
        "size": 43,
        "text": "\\u201crestrictive"
    },
    {
        "size": 43,
        "text": "\\ud83d\\udea8"
    },
    {
        "size": 43,
        "text": "agree"
    },
    {
        "size": 43,
        "text": "corecivic\\u2019s"
    },
    {
        "size": 43,
        "text": "education"
    },
    {
        "size": 43,
        "text": "euphemistically"
    },
    {
        "size": 43,
        "text": "force"
    },
    {
        "size": 43,
        "text": "information"
    },
    {
        "size": 43,
        "text": "interesting"
    }
];
