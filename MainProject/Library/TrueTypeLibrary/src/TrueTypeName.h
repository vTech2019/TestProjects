#ifndef __TRUETYPENAME_H__
#define __TRUETYPENAME_H__
#include <stdint.h>

#include "TrueTypeMath.h"
enum e_TrueTypeNamePlatformID {
    TrueTypeNamePlatformID_Unicode,
    TrueTypeNamePlatformID_Macintosh,
    TrueTypeNamePlatformID_ISO,
    TrueTypeNamePlatformID_Windows,
    TrueTypeNamePlatformID_Custom
};
enum e_TrueTypeNameEncodingID_Platform0 {
    TrueTypeNameEncodingIDPlatform0_Unicode1_0,
    TrueTypeNameEncodingIDPlatform0_Unicode1_1,
    TrueTypeNameEncodingIDPlatform0_ISO_IEC10646,
    TrueTypeNameEncodingIDPlatform0_Unicode2_0_cmap_0_4_6,
    TrueTypeNameEncodingIDPlatform0_Unicode2_0_cmap_0_4_6_10_12,
    TrueTypeNameEncodingIDPlatform0_Unicode_Variation_cmap_14,
    TrueTypeNameEncodingIDPlatform0_Unicode_full_cmap_0_4_6_10_12_13
};
enum e_TrueTypeNameEncodingID_Platform3 {
    TrueTypeNameEncodingIDPlatform3_Symbol,
    TrueTypeNameEncodingIDPlatform3_Unicode_BMP,
    TrueTypeNameEncodingIDPlatform3_ShiftJIS,
    TrueTypeNameEncodingIDPlatform3_PRC,
    TrueTypeNameEncodingIDPlatform3_Big5,
    TrueTypeNameEncodingIDPlatform3_Wansung,
    TrueTypeNameEncodingIDPlatform3_Johab,
    TrueTypeNameEncodingIDPlatform3_Reserved_0,
    TrueTypeNameEncodingIDPlatform3_Reserved_1,
    TrueTypeNameEncodingIDPlatform3_Reserved_2,
    TrueTypeNameEncodingIDPlatform3_Unicode_full
};
enum e_TrueTypeNameLanguageIDApple {
    TrueTypeNameLanguageIDApple_English,
    TrueTypeNameLanguageIDApple_French,
    TrueTypeNameLanguageIDApple_German,
    TrueTypeNameLanguageIDApple_Italian,
    TrueTypeNameLanguageIDApple_Dutch,
    TrueTypeNameLanguageIDApple_Swedish,
    TrueTypeNameLanguageIDApple_Spanish,
    TrueTypeNameLanguageIDApple_Danish,
    TrueTypeNameLanguageIDApple_Portuguese,
    TrueTypeNameLanguageIDApple_Norwegian,
    TrueTypeNameLanguageIDApple_Hebrew,
    TrueTypeNameLanguageIDApple_Japanese,
    TrueTypeNameLanguageIDApple_Arabic,
    TrueTypeNameLanguageIDApple_Finnish,
    TrueTypeNameLanguageIDApple_Greek,
    TrueTypeNameLanguageIDApple_Icelandic,
    TrueTypeNameLanguageIDApple_Maltese,
    TrueTypeNameLanguageIDApple_Turkish,
    TrueTypeNameLanguageIDApple_Croatian,
    TrueTypeNameLanguageIDApple_Chinese_Traditional,
    TrueTypeNameLanguageIDApple_Urdu,
    TrueTypeNameLanguageIDApple_Hindi,
    TrueTypeNameLanguageIDApple_Thai,
    TrueTypeNameLanguageIDApple_Korean,
    TrueTypeNameLanguageIDApple_Lithuanian,
    TrueTypeNameLanguageIDApple_Polish,
    TrueTypeNameLanguageIDApple_Hungarian,
    TrueTypeNameLanguageIDApple_Estonian,
    TrueTypeNameLanguageIDApple_Latvian,
    TrueTypeNameLanguageIDApple_Sami,
    TrueTypeNameLanguageIDApple_Faroese,
    TrueTypeNameLanguageIDApple_Farsi_Persian,
    TrueTypeNameLanguageIDApple_Russian,
    TrueTypeNameLanguageIDApple_Chinese_Simplified,
    TrueTypeNameLanguageIDApple_Flemish,
    TrueTypeNameLanguageIDApple_Irish_Gaelic,
    TrueTypeNameLanguageIDApple_Albanian,
    TrueTypeNameLanguageIDApple_Romanian,
    TrueTypeNameLanguageIDApple_Czech,
    TrueTypeNameLanguageIDApple_Slovak,
    TrueTypeNameLanguageIDApple_Slovenian,
    TrueTypeNameLanguageIDApple_Yiddish,
    TrueTypeNameLanguageIDApple_Serbian,
    TrueTypeNameLanguageIDApple_Macedonian,
    TrueTypeNameLanguageIDApple_Bulgarian,
    TrueTypeNameLanguageIDApple_Ukrainian,
    TrueTypeNameLanguageIDApple_Byelorussian,
    TrueTypeNameLanguageIDApple_Uzbek,
    TrueTypeNameLanguageIDApple_Kazakh,
    TrueTypeNameLanguageIDApple_Azerbaijani_Cyrillic_script,
    TrueTypeNameLanguageIDApple_Azerbaijani_Arabic_script,
    TrueTypeNameLanguageIDApple_Armenian,
    TrueTypeNameLanguageIDApple_Georgian,
    TrueTypeNameLanguageIDApple_Moldavian,
    TrueTypeNameLanguageIDApple_Kirghiz,
    TrueTypeNameLanguageIDApple_Tajiki,
    TrueTypeNameLanguageIDApple_Turkmen,
    TrueTypeNameLanguageIDApple_Mongolian_Mongolian_script,
    TrueTypeNameLanguageIDApple_Mongolian_Cyrillic_script,
    TrueTypeNameLanguageIDApple_Pashto,
    TrueTypeNameLanguageIDApple_Kurdish,
    TrueTypeNameLanguageIDApple_Kashmiri,
    TrueTypeNameLanguageIDApple_Sindhi,
    TrueTypeNameLanguageIDApple_Tibetan,
    TrueTypeNameLanguageIDApple_Nepali,
    TrueTypeNameLanguageIDApple_Sanskrit,
    TrueTypeNameLanguageIDApple_Marathi,
    TrueTypeNameLanguageIDApple_Bengali,
    TrueTypeNameLanguageIDApple_Assamese,
    TrueTypeNameLanguageIDApple_Gujarati,
    TrueTypeNameLanguageIDApple_Punjabi,
    TrueTypeNameLanguageIDApple_Oriya,
    TrueTypeNameLanguageIDApple_Malayalam,
    TrueTypeNameLanguageIDApple_Kannada,
    TrueTypeNameLanguageIDApple_Tamil,
    TrueTypeNameLanguageIDApple_Telugu,
    TrueTypeNameLanguageIDApple_Sinhalese,
    TrueTypeNameLanguageIDApple_Burmese,
    TrueTypeNameLanguageIDApple_Khmer,
    TrueTypeNameLanguageIDApple_Lao,
    TrueTypeNameLanguageIDApple_Vietnamese,
    TrueTypeNameLanguageIDApple_Indonesian,
    TrueTypeNameLanguageIDApple_Tagalog,
    TrueTypeNameLanguageIDApple_Malay_Roman_script,
    TrueTypeNameLanguageIDApple_Malay_Arabic_script,
    TrueTypeNameLanguageIDApple_Amharic,
    TrueTypeNameLanguageIDApple_Tigrinya,
    TrueTypeNameLanguageIDApple_Galla,
    TrueTypeNameLanguageIDApple_Somali,
    TrueTypeNameLanguageIDApple_Swahili,
    TrueTypeNameLanguageIDApple_Kinyarwanda_Ruanda,
    TrueTypeNameLanguageIDApple_Rundi,
    TrueTypeNameLanguageIDApple_Nyanja_Chewa,
    TrueTypeNameLanguageIDApple_Malagasy,
    TrueTypeNameLanguageIDApple_Esperanto,
    TrueTypeNameLanguageIDApple_Welsh = 128,
    TrueTypeNameLanguageIDApple_Basque,
    TrueTypeNameLanguageIDApple_Catalan,
    TrueTypeNameLanguageIDApple_Latin,
    TrueTypeNameLanguageIDApple_Quechua,
    TrueTypeNameLanguageIDApple_Guarani,
    TrueTypeNameLanguageIDApple_Aymara,
    TrueTypeNameLanguageIDApple_Tatar,
    TrueTypeNameLanguageIDApple_Uighur,
    TrueTypeNameLanguageIDApple_Dzongkha,
    TrueTypeNameLanguageIDApple_Javanese_Roman_script,
    TrueTypeNameLanguageIDApple_Sundanese_Roman_script,
    TrueTypeNameLanguageIDApple_Galician,
    TrueTypeNameLanguageIDApple_Afrikaans,
    TrueTypeNameLanguageIDApple_Breton,
    TrueTypeNameLanguageIDApple_Inuktitut,
    TrueTypeNameLanguageIDApple_Scottish_Gaelic,
    TrueTypeNameLanguageIDApple_Manx_Gaelic,
    TrueTypeNameLanguageIDApple_Irish_Gaelic_with_dot_above,
    TrueTypeNameLanguageIDApple_Tongan,
    TrueTypeNameLanguageIDApple_Greek_polytonic,
    TrueTypeNameLanguageIDApple_Greenlandic,
    TrueTypeNameLanguageIDApple_Azerbaijani_Roman_script
};
enum e_TrueTypeNameLanguageIDMicrosoft {
    TrueTypeNameLanguageIDMicrosoft_Afrikaans_SouthAfrica = 0x0436,
    TrueTypeNameLanguageIDMicrosoft_Albanian_Albania = 0x041C,
    TrueTypeNameLanguageIDMicrosoft_Alsatian_France = 0x0484,
    TrueTypeNameLanguageIDMicrosoft_Amharic_Ethiopia = 0x045E,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Algeria = 0x1401,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Bahrain = 0x3C01,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Egypt = 0x0C01,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Iraq = 0x0801,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Jordan = 0x2C01,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Kuwait = 0x3401,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Lebanon = 0x3001,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Libya = 0x1001,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Morocco = 0x1801,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Oman = 0x2001,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Qatar = 0x4001,
    TrueTypeNameLanguageIDMicrosoft_Arabic_SaudiArabia = 0x0401,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Syria = 0x2801,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Tunisia = 0x1C01,
    TrueTypeNameLanguageIDMicrosoft_Arabic_UAE = 0x3801,
    TrueTypeNameLanguageIDMicrosoft_Arabic_Yemen = 0x2401,
    TrueTypeNameLanguageIDMicrosoft_Armenian_Armenia = 0x042B,
    TrueTypeNameLanguageIDMicrosoft_Assamese_India = 0x044D,
    TrueTypeNameLanguageIDMicrosoft_AzeriCyrillic_Azerbaijan = 0x082C,
    TrueTypeNameLanguageIDMicrosoft_AzeriLatin_Azerbaijan = 0x042C,
    TrueTypeNameLanguageIDMicrosoft_Bashkir_Russia = 0x046D,
    TrueTypeNameLanguageIDMicrosoft_Basque_Basque = 0x042D,
    TrueTypeNameLanguageIDMicrosoft_Belarusian_Belarus = 0x0423,
    TrueTypeNameLanguageIDMicrosoft_Bengali_Bangladesh = 0x0845,
    TrueTypeNameLanguageIDMicrosoft_Bengali_India = 0x0445,
    TrueTypeNameLanguageIDMicrosoft_BosnianCyrillic_BosniaAndHerzegovina = 0x201A,
    TrueTypeNameLanguageIDMicrosoft_BosnianLatin_BosniaAndHerzegovina = 0x141A,
    TrueTypeNameLanguageIDMicrosoft_Breton_France = 0x047E,
    TrueTypeNameLanguageIDMicrosoft_Bulgarian_Bulgaria = 0x0402,
    TrueTypeNameLanguageIDMicrosoft_Catalan_Catalan = 0x0403,
    TrueTypeNameLanguageIDMicrosoft_Chinese_HongKongSAR = 0x0C04,
    TrueTypeNameLanguageIDMicrosoft_Chinese_MacaoSAR = 0x1404,
    TrueTypeNameLanguageIDMicrosoft_Chinese_PeoplesRepublicOfChina = 0x0804,
    TrueTypeNameLanguageIDMicrosoft_Chinese_Singapore = 0x1004,
    TrueTypeNameLanguageIDMicrosoft_Chinese_Taiwan = 0x0404,
    TrueTypeNameLanguageIDMicrosoft_Corsican_France = 0x0483,
    TrueTypeNameLanguageIDMicrosoft_Croatian_Croatia = 0x041A,
    TrueTypeNameLanguageIDMicrosoft_CroatianLatin_BosniaAndHerzegovina = 0x101A,
    TrueTypeNameLanguageIDMicrosoft_Czech_CzechRepublic = 0x0405,
    TrueTypeNameLanguageIDMicrosoft_Danish_Denmark = 0x0406,
    TrueTypeNameLanguageIDMicrosoft_Dari_Afghanistan = 0x048C,
    TrueTypeNameLanguageIDMicrosoft_Divehi_Maldives = 0x0465,
    TrueTypeNameLanguageIDMicrosoft_Dutch_Belgium = 0x0813,
    TrueTypeNameLanguageIDMicrosoft_Dutch_Netherlands = 0x0413,
    TrueTypeNameLanguageIDMicrosoft_English_Australia = 0x0C09,
    TrueTypeNameLanguageIDMicrosoft_English_Belize = 0x2809,
    TrueTypeNameLanguageIDMicrosoft_English_Canada = 0x1009,
    TrueTypeNameLanguageIDMicrosoft_English_Caribbean = 0x2409,
    TrueTypeNameLanguageIDMicrosoft_English_India = 0x4009,
    TrueTypeNameLanguageIDMicrosoft_English_Ireland = 0x1809,
    TrueTypeNameLanguageIDMicrosoft_English_Jamaica = 0x2009,
    TrueTypeNameLanguageIDMicrosoft_English_Malaysia = 0x4409,
    TrueTypeNameLanguageIDMicrosoft_English_NewZealand = 0x1409,
    TrueTypeNameLanguageIDMicrosoft_English_RepublicOfThePhilippines = 0x3409,
    TrueTypeNameLanguageIDMicrosoft_English_Singapore = 0x4809,
    TrueTypeNameLanguageIDMicrosoft_English_SouthAfrica = 0x1C09,
    TrueTypeNameLanguageIDMicrosoft_English_TrinidadAndTobago = 0x2C09,
    TrueTypeNameLanguageIDMicrosoft_English_UnitedKingdom = 0x0809,
    TrueTypeNameLanguageIDMicrosoft_English_UnitedStates = 0x0409,
    TrueTypeNameLanguageIDMicrosoft_English_Zimbabwe = 0x3009,
    TrueTypeNameLanguageIDMicrosoft_Estonian_Estonia = 0x0425,
    TrueTypeNameLanguageIDMicrosoft_Faroese_FaroeIslands = 0x0438,
    TrueTypeNameLanguageIDMicrosoft_Filipino_Philippines = 0x0464,
    TrueTypeNameLanguageIDMicrosoft_Finnish_Finland = 0x040B,
    TrueTypeNameLanguageIDMicrosoft_French_Belgium = 0x080C,
    TrueTypeNameLanguageIDMicrosoft_French_Canada = 0x0C0C,
    TrueTypeNameLanguageIDMicrosoft_French_France = 0x040C,
    TrueTypeNameLanguageIDMicrosoft_French_Luxembourg = 0x140c,
    TrueTypeNameLanguageIDMicrosoft_French_PrincipalityOfMonaco = 0x180C,
    TrueTypeNameLanguageIDMicrosoft_French_Switzerland = 0x100C,
    TrueTypeNameLanguageIDMicrosoft_Frisian_Netherlands = 0x0462,
    TrueTypeNameLanguageIDMicrosoft_Galician_Galician = 0x0456,
    TrueTypeNameLanguageIDMicrosoft_Georgian_Georgia = 0x0437,
    TrueTypeNameLanguageIDMicrosoft_German_Austria = 0x0C07,
    TrueTypeNameLanguageIDMicrosoft_German_Germany = 0x0407,
    TrueTypeNameLanguageIDMicrosoft_German_Liechtenstein = 0x1407,
    TrueTypeNameLanguageIDMicrosoft_German_Luxembourg = 0x1007,
    TrueTypeNameLanguageIDMicrosoft_German_Switzerland = 0x0807,
    TrueTypeNameLanguageIDMicrosoft_Greek_Greece = 0x0408,
    TrueTypeNameLanguageIDMicrosoft_Greenlandic_Greenland = 0x046F,
    TrueTypeNameLanguageIDMicrosoft_Gujarati_India = 0x0447,
    TrueTypeNameLanguageIDMicrosoft_HausaLatin_Nigeria = 0x0468,
    TrueTypeNameLanguageIDMicrosoft_Hebrew_Israel = 0x040D,
    TrueTypeNameLanguageIDMicrosoft_Hindi_India = 0x0439,
    TrueTypeNameLanguageIDMicrosoft_Hungarian_Hungary = 0x040E,
    TrueTypeNameLanguageIDMicrosoft_Icelandic_Iceland = 0x040F,
    TrueTypeNameLanguageIDMicrosoft_Igbo_Nigeria = 0x0470,
    TrueTypeNameLanguageIDMicrosoft_Indonesian_Indonesia = 0x0421,
    TrueTypeNameLanguageIDMicrosoft_Inuktitut_Canada = 0x045D,
    TrueTypeNameLanguageIDMicrosoft_InuktitutLatin_Canada = 0x085D,
    TrueTypeNameLanguageIDMicrosoft_Irish_Ireland = 0x083C,
    TrueTypeNameLanguageIDMicrosoft_isiXhosa_SouthAfrica = 0x0434,
    TrueTypeNameLanguageIDMicrosoft_isiZulu_SouthAfrica = 0x0435,
    TrueTypeNameLanguageIDMicrosoft_Italian_Italy = 0x0410,
    TrueTypeNameLanguageIDMicrosoft_Italian_Switzerland = 0x0810,
    TrueTypeNameLanguageIDMicrosoft_Japanese_Japan = 0x0411,
    TrueTypeNameLanguageIDMicrosoft_Kannada_India = 0x044B,
    TrueTypeNameLanguageIDMicrosoft_Kazakh_Kazakhstan = 0x043F,
    TrueTypeNameLanguageIDMicrosoft_Khmer_Cambodia = 0x0453,
    TrueTypeNameLanguageIDMicrosoft_Kiche_Guatemala = 0x0486,
    TrueTypeNameLanguageIDMicrosoft_Kinyarwanda_Rwanda = 0x0487,
    TrueTypeNameLanguageIDMicrosoft_Kiswahili_Kenya = 0x0441,
    TrueTypeNameLanguageIDMicrosoft_Konkani_India = 0x0457,
    TrueTypeNameLanguageIDMicrosoft_Korean_Korea = 0x0412,
    TrueTypeNameLanguageIDMicrosoft_Kyrgyz_Kyrgyzstan = 0x0440,
    TrueTypeNameLanguageIDMicrosoft_Lao_LaoPDR = 0x0454,
    TrueTypeNameLanguageIDMicrosoft_Latvian_Latvia = 0x0426,
    TrueTypeNameLanguageIDMicrosoft_Lithuanian_Lithuania = 0x0427,
    TrueTypeNameLanguageIDMicrosoft_LowerSorbian_Germany = 0x082E,
    TrueTypeNameLanguageIDMicrosoft_Luxembourgish_Luxembourg = 0x046E,
    TrueTypeNameLanguageIDMicrosoft_MacedonianFYROM_FormerYugoslavRepublicOfMacedonia = 0x042F,
    TrueTypeNameLanguageIDMicrosoft_Malay_BruneiDarussalam = 0x083E,
    TrueTypeNameLanguageIDMicrosoft_Malay_Malaysia = 0x043E,
    TrueTypeNameLanguageIDMicrosoft_Malayalam_India = 0x044C,
    TrueTypeNameLanguageIDMicrosoft_Maltese_Malta = 0x043A,
    TrueTypeNameLanguageIDMicrosoft_Maori_NewZealand = 0x0481,
    TrueTypeNameLanguageIDMicrosoft_Mapudungun_Chile = 0x047A,
    TrueTypeNameLanguageIDMicrosoft_Marathi_India = 0x044E,
    TrueTypeNameLanguageIDMicrosoft_Mohawk_Mohawk = 0x047C,
    TrueTypeNameLanguageIDMicrosoft_MongolianCyrillic_Mongolia = 0x0450,
    TrueTypeNameLanguageIDMicrosoft_MongolianTraditional_PeoplesRepublicOfChina = 0x0850,
    TrueTypeNameLanguageIDMicrosoft_Nepali_Nepal = 0x0461,
    TrueTypeNameLanguageIDMicrosoft_NorwegianBokmal_Norway = 0x0414,
    TrueTypeNameLanguageIDMicrosoft_NorwegianNynorsk_Norway = 0x0814,
    TrueTypeNameLanguageIDMicrosoft_Occitan_France = 0x0482,
    TrueTypeNameLanguageIDMicrosoft_OdiaformerlyOriya_India = 0x0448,
    TrueTypeNameLanguageIDMicrosoft_Pashto_Afghanistan = 0x0463,
    TrueTypeNameLanguageIDMicrosoft_Polish_Poland = 0x0415,
    TrueTypeNameLanguageIDMicrosoft_Portuguese_Brazil = 0x0416,
    TrueTypeNameLanguageIDMicrosoft_Portuguese_Portugal = 0x0816,
    TrueTypeNameLanguageIDMicrosoft_Punjabi_India = 0x0446,
    TrueTypeNameLanguageIDMicrosoft_Quechua_Bolivia = 0x046B,
    TrueTypeNameLanguageIDMicrosoft_Quechua_Ecuador = 0x086B,
    TrueTypeNameLanguageIDMicrosoft_Quechua_Peru = 0x0C6B,
    TrueTypeNameLanguageIDMicrosoft_Romanian_Romania = 0x0418,
    TrueTypeNameLanguageIDMicrosoft_Romansh_Switzerland = 0x0417,
    TrueTypeNameLanguageIDMicrosoft_Russian_Russia = 0x0419,
    TrueTypeNameLanguageIDMicrosoft_SamiInari_Finland = 0x243B,
    TrueTypeNameLanguageIDMicrosoft_SamiLule_Norway = 0x103B,
    TrueTypeNameLanguageIDMicrosoft_SamiLule_Sweden = 0x143B,
    TrueTypeNameLanguageIDMicrosoft_SamiNorthern_Finland = 0x0C3B,
    TrueTypeNameLanguageIDMicrosoft_SamiNorthern_Norway = 0x043B,
    TrueTypeNameLanguageIDMicrosoft_SamiNorthern_Sweden = 0x083B,
    TrueTypeNameLanguageIDMicrosoft_SamiSkolt_Finland = 0x203B,
    TrueTypeNameLanguageIDMicrosoft_SamiSouthern_Norway = 0x183B,
    TrueTypeNameLanguageIDMicrosoft_SamiSouthern_Sweden = 0x1C3B,
    TrueTypeNameLanguageIDMicrosoft_Sanskrit_India = 0x044F,
    TrueTypeNameLanguageIDMicrosoft_SerbianCyrillic_BosniaAndHerzegovina = 0x1C1A,
    TrueTypeNameLanguageIDMicrosoft_SerbianCyrillic_Serbia = 0x0C1A,
    TrueTypeNameLanguageIDMicrosoft_SerbianLatin_BosniaAndHerzegovina = 0x181A,
    TrueTypeNameLanguageIDMicrosoft_SerbianLatin_Serbia = 0x081A,
    TrueTypeNameLanguageIDMicrosoft_SesothoSaLeboa_SouthAfrica = 0x046C,
    TrueTypeNameLanguageIDMicrosoft_Setswana_SouthAfrica = 0x0432,
    TrueTypeNameLanguageIDMicrosoft_Sinhala_SriLanka = 0x045B,
    TrueTypeNameLanguageIDMicrosoft_Slovak_Slovakia = 0x041B,
    TrueTypeNameLanguageIDMicrosoft_Slovenian_Slovenia = 0x0424,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Argentina = 0x2C0A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Bolivia = 0x400A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Chile = 0x340A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Colombia = 0x240A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_CostaRica = 0x140A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_DominicanRepublic = 0x1C0A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Ecuador = 0x300A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_ElSalvador = 0x440A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Guatemala = 0x100A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Honduras = 0x480A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Mexico = 0x080A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Nicaragua = 0x4C0A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Panama = 0x180A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Paraguay = 0x3C0A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Peru = 0x280A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_PuertoRico = 0x500A,
    TrueTypeNameLanguageIDMicrosoft_SpanishModernSort_Spain = 0x0C0A,
    TrueTypeNameLanguageIDMicrosoft_SpanishTraditionalSort_Spain = 0x040A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_UnitedStates = 0x540A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Uruguay = 0x380A,
    TrueTypeNameLanguageIDMicrosoft_Spanish_Venezuela = 0x200A,
    TrueTypeNameLanguageIDMicrosoft_Sweden_Finland = 0x081D,
    TrueTypeNameLanguageIDMicrosoft_Swedish_Sweden = 0x041D,
    TrueTypeNameLanguageIDMicrosoft_Syriac_Syria = 0x045A,
    TrueTypeNameLanguageIDMicrosoft_TajikCyrillic_Tajikistan = 0x0428,
    TrueTypeNameLanguageIDMicrosoft_TamazightLatin_Algeria = 0x085F,
    TrueTypeNameLanguageIDMicrosoft_Tamil_India = 0x0449,
    TrueTypeNameLanguageIDMicrosoft_Tatar_Russia = 0x0444,
    TrueTypeNameLanguageIDMicrosoft_Telugu_India = 0x044A,
    TrueTypeNameLanguageIDMicrosoft_Thai_Thailand = 0x041E,
    TrueTypeNameLanguageIDMicrosoft_Tibetan_PRC = 0x0451,
    TrueTypeNameLanguageIDMicrosoft_Turkish_Turkey = 0x041F,
    TrueTypeNameLanguageIDMicrosoft_Turkmen_Turkmenistan = 0x0442,
    TrueTypeNameLanguageIDMicrosoft_Uighur_PRC = 0x0480,
    TrueTypeNameLanguageIDMicrosoft_Ukrainian_Ukraine = 0x0422,
    TrueTypeNameLanguageIDMicrosoft_Upper_Germany = 0x042E,
    TrueTypeNameLanguageIDMicrosoft_Urdu_IslamicRepublicOfPakistan = 0x0420,
    TrueTypeNameLanguageIDMicrosoft_UzbekCyrillic_Uzbekistan = 0x0843,
    TrueTypeNameLanguageIDMicrosoft_UzbekLatin_Uzbekistan = 0x0443,
    TrueTypeNameLanguageIDMicrosoft_Vietnamese_Vietnam = 0x042A,
    TrueTypeNameLanguageIDMicrosoft_Welsh_UnitedKingdom = 0x0452,
    TrueTypeNameLanguageIDMicrosoft_Wolof_Senegal = 0x0488,
    TrueTypeNameLanguageIDMicrosoft_Yakut_Russia = 0x0485,
    TrueTypeNameLanguageIDMicrosoft_Yi_PRC = 0x0478,
    TrueTypeNameLanguageIDMicrosoft_Yoruba_Nigeria = 0x046A
};
struct TrueTypeNameLangTagRecord_header_t {
    uint16_t length;
    uint16_t offset;
};
struct TrueTypeNameLangTagRecord_t {
    uint16_t length;
    uint8_t* tag;
};
struct TrueTypeNameRecords_header_t {
    uint16_t platformID;
    uint16_t encodingID;
    uint16_t languageID;
    uint16_t nameID;
    uint16_t length;
    uint16_t offset;
};
struct TrueTypeNameRecords_t {
    uint16_t platformID;
    uint16_t encodingID;
    uint16_t languageID;
    uint16_t nameID;
    uint16_t length;
    uint8_t* nameRecord;
};
struct TrueTypeNameV1_header_t {
    uint16_t langTagCount;
    struct TrueTypeNameLangTagRecord_header_t langTagRecord[];
};
struct TrueTypeNameV1_t {
    uint16_t langTagCount;
    struct TrueTypeNameLangTagRecord_t langTagRecord[];
};
struct TrueTypeName_header_t {
    uint16_t format;
    uint16_t count;
    uint16_t stringOffset;
    struct TrueTypeNameRecords_header_t nameRecord[];
};
typedef struct _TrueTypeName_t {
    uint16_t format;
    uint16_t count;
    uint16_t stringOffset;
    struct TrueTypeNameRecords_t* nameRecord;
    struct TrueTypeNameV1_t* langTagRecord;
}TrueTypeName_t;

static struct TrueTypeName_header_t TrueTypeName_header(TrueTypeName_header_t* table) {
    struct TrueTypeNameV1_header_t* m_ptr_langTagRecord;
    uint32_t i, j;
    table->format = SWAP_BYTE_16(table->format);
    table->count = SWAP_BYTE_16(table->count);
    table->stringOffset = SWAP_BYTE_16(table->stringOffset);
    m_ptr_langTagRecord = table->format == 1
        ? (struct TrueTypeNameV1_header_t*)(table->nameRecord + table->count)
        : NULL;
    for (i = 0; i < table->count; i++) {
        table->nameRecord[i].platformID = SWAP_BYTE_16(table->nameRecord[i].platformID);
        table->nameRecord[i].encodingID = SWAP_BYTE_16(table->nameRecord[i].encodingID);
        table->nameRecord[i].languageID = SWAP_BYTE_16(table->nameRecord[i].languageID);
        table->nameRecord[i].nameID = SWAP_BYTE_16(table->nameRecord[i].nameID);
        table->nameRecord[i].length = SWAP_BYTE_16(table->nameRecord[i].length);
        table->nameRecord[i].offset = SWAP_BYTE_16(table->nameRecord[i].offset);
    }
    if (m_ptr_langTagRecord) {
        m_ptr_langTagRecord->langTagCount = SWAP_BYTE_16(m_ptr_langTagRecord->langTagCount);
        for (i = 0; i < m_ptr_langTagRecord->langTagCount; i++) {
            m_ptr_langTagRecord->langTagRecord[i].length = SWAP_BYTE_16(m_ptr_langTagRecord->langTagRecord[i].length);
            m_ptr_langTagRecord->langTagRecord[i].offset = SWAP_BYTE_16(m_ptr_langTagRecord->langTagRecord[i].offset);
        }
    }
    return *table;
}

#endif
