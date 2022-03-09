///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2022.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <cstdint>

#include <examples/example_decwide_t.h>
#include <math/wide_decimal/decwide_t.h>

#if defined(WIDE_DECIMAL_NAMESPACE)
auto WIDE_DECIMAL_NAMESPACE::math::wide_decimal::example001d_pow2_from_list() -> bool
#else
auto math::wide_decimal::example001d_pow2_from_list() -> bool
#endif
{
  using local_limb_type = std::uint32_t;

  constexpr std::int32_t wide_decimal_digits10 = INT32_C(100);

  using wide_decimal_type = math::wide_decimal::decwide_t<wide_decimal_digits10, local_limb_type, void>;

  // Column[Table[N[2^n, 100], {n, -128, 127, 1}]]
  // ... and copy as plain text.
  using local_pow2_data_type = std::array<wide_decimal_type, static_cast<std::size_t>(UINT32_C(256))>;

  static const local_pow2_data_type local_pow2_data =
  {{
    wide_decimal_type("2.938735877055718769921841343055614194546663891930218803771879265696043148636817932128906250000000000E-39"),
    wide_decimal_type("5.877471754111437539843682686111228389093327783860437607543758531392086297273635864257812500000000000E-39"),
    wide_decimal_type("1.175494350822287507968736537222245677818665556772087521508751706278417259454727172851562500000000000E-38"),
    wide_decimal_type("2.350988701644575015937473074444491355637331113544175043017503412556834518909454345703125000000000000E-38"),
    wide_decimal_type("4.701977403289150031874946148888982711274662227088350086035006825113669037818908691406250000000000000E-38"),
    wide_decimal_type("9.403954806578300063749892297777965422549324454176700172070013650227338075637817382812500000000000000E-38"),
    wide_decimal_type("1.880790961315660012749978459555593084509864890835340034414002730045467615127563476562500000000000000E-37"),
    wide_decimal_type("3.761581922631320025499956919111186169019729781670680068828005460090935230255126953125000000000000000E-37"),
    wide_decimal_type("7.523163845262640050999913838222372338039459563341360137656010920181870460510253906250000000000000000E-37"),
    wide_decimal_type("1.504632769052528010199982767644474467607891912668272027531202184036374092102050781250000000000000000E-36"),
    wide_decimal_type("3.009265538105056020399965535288948935215783825336544055062404368072748184204101562500000000000000000E-36"),
    wide_decimal_type("6.018531076210112040799931070577897870431567650673088110124808736145496368408203125000000000000000000E-36"),
    wide_decimal_type("1.203706215242022408159986214115579574086313530134617622024961747229099273681640625000000000000000000E-35"),
    wide_decimal_type("2.407412430484044816319972428231159148172627060269235244049923494458198547363281250000000000000000000E-35"),
    wide_decimal_type("4.814824860968089632639944856462318296345254120538470488099846988916397094726562500000000000000000000E-35"),
    wide_decimal_type("9.629649721936179265279889712924636592690508241076940976199693977832794189453125000000000000000000000E-35"),
    wide_decimal_type("1.925929944387235853055977942584927318538101648215388195239938795566558837890625000000000000000000000E-34"),
    wide_decimal_type("3.851859888774471706111955885169854637076203296430776390479877591133117675781250000000000000000000000E-34"),
    wide_decimal_type("7.703719777548943412223911770339709274152406592861552780959755182266235351562500000000000000000000000E-34"),
    wide_decimal_type("1.540743955509788682444782354067941854830481318572310556191951036453247070312500000000000000000000000E-33"),
    wide_decimal_type("3.081487911019577364889564708135883709660962637144621112383902072906494140625000000000000000000000000E-33"),
    wide_decimal_type("6.162975822039154729779129416271767419321925274289242224767804145812988281250000000000000000000000000E-33"),
    wide_decimal_type("1.232595164407830945955825883254353483864385054857848444953560829162597656250000000000000000000000000E-32"),
    wide_decimal_type("2.465190328815661891911651766508706967728770109715696889907121658325195312500000000000000000000000000E-32"),
    wide_decimal_type("4.930380657631323783823303533017413935457540219431393779814243316650390625000000000000000000000000000E-32"),
    wide_decimal_type("9.860761315262647567646607066034827870915080438862787559628486633300781250000000000000000000000000000E-32"),
    wide_decimal_type("1.972152263052529513529321413206965574183016087772557511925697326660156250000000000000000000000000000E-31"),
    wide_decimal_type("3.944304526105059027058642826413931148366032175545115023851394653320312500000000000000000000000000000E-31"),
    wide_decimal_type("7.888609052210118054117285652827862296732064351090230047702789306640625000000000000000000000000000000E-31"),
    wide_decimal_type("1.577721810442023610823457130565572459346412870218046009540557861328125000000000000000000000000000000E-30"),
    wide_decimal_type("3.155443620884047221646914261131144918692825740436092019081115722656250000000000000000000000000000000E-30"),
    wide_decimal_type("6.310887241768094443293828522262289837385651480872184038162231445312500000000000000000000000000000000E-30"),
    wide_decimal_type("1.262177448353618888658765704452457967477130296174436807632446289062500000000000000000000000000000000E-29"),
    wide_decimal_type("2.524354896707237777317531408904915934954260592348873615264892578125000000000000000000000000000000000E-29"),
    wide_decimal_type("5.048709793414475554635062817809831869908521184697747230529785156250000000000000000000000000000000000E-29"),
    wide_decimal_type("1.009741958682895110927012563561966373981704236939549446105957031250000000000000000000000000000000000E-28"),
    wide_decimal_type("2.019483917365790221854025127123932747963408473879098892211914062500000000000000000000000000000000000E-28"),
    wide_decimal_type("4.038967834731580443708050254247865495926816947758197784423828125000000000000000000000000000000000000E-28"),
    wide_decimal_type("8.077935669463160887416100508495730991853633895516395568847656250000000000000000000000000000000000000E-28"),
    wide_decimal_type("1.615587133892632177483220101699146198370726779103279113769531250000000000000000000000000000000000000E-27"),
    wide_decimal_type("3.231174267785264354966440203398292396741453558206558227539062500000000000000000000000000000000000000E-27"),
    wide_decimal_type("6.462348535570528709932880406796584793482907116413116455078125000000000000000000000000000000000000000E-27"),
    wide_decimal_type("1.292469707114105741986576081359316958696581423282623291015625000000000000000000000000000000000000000E-26"),
    wide_decimal_type("2.584939414228211483973152162718633917393162846565246582031250000000000000000000000000000000000000000E-26"),
    wide_decimal_type("5.169878828456422967946304325437267834786325693130493164062500000000000000000000000000000000000000000E-26"),
    wide_decimal_type("1.033975765691284593589260865087453566957265138626098632812500000000000000000000000000000000000000000E-25"),
    wide_decimal_type("2.067951531382569187178521730174907133914530277252197265625000000000000000000000000000000000000000000E-25"),
    wide_decimal_type("4.135903062765138374357043460349814267829060554504394531250000000000000000000000000000000000000000000E-25"),
    wide_decimal_type("8.271806125530276748714086920699628535658121109008789062500000000000000000000000000000000000000000000E-25"),
    wide_decimal_type("1.654361225106055349742817384139925707131624221801757812500000000000000000000000000000000000000000000E-24"),
    wide_decimal_type("3.308722450212110699485634768279851414263248443603515625000000000000000000000000000000000000000000000E-24"),
    wide_decimal_type("6.617444900424221398971269536559702828526496887207031250000000000000000000000000000000000000000000000E-24"),
    wide_decimal_type("1.323488980084844279794253907311940565705299377441406250000000000000000000000000000000000000000000000E-23"),
    wide_decimal_type("2.646977960169688559588507814623881131410598754882812500000000000000000000000000000000000000000000000E-23"),
    wide_decimal_type("5.293955920339377119177015629247762262821197509765625000000000000000000000000000000000000000000000000E-23"),
    wide_decimal_type("1.058791184067875423835403125849552452564239501953125000000000000000000000000000000000000000000000000E-22"),
    wide_decimal_type("2.117582368135750847670806251699104905128479003906250000000000000000000000000000000000000000000000000E-22"),
    wide_decimal_type("4.235164736271501695341612503398209810256958007812500000000000000000000000000000000000000000000000000E-22"),
    wide_decimal_type("8.470329472543003390683225006796419620513916015625000000000000000000000000000000000000000000000000000E-22"),
    wide_decimal_type("1.694065894508600678136645001359283924102783203125000000000000000000000000000000000000000000000000000E-21"),
    wide_decimal_type("3.388131789017201356273290002718567848205566406250000000000000000000000000000000000000000000000000000E-21"),
    wide_decimal_type("6.776263578034402712546580005437135696411132812500000000000000000000000000000000000000000000000000000E-21"),
    wide_decimal_type("1.355252715606880542509316001087427139282226562500000000000000000000000000000000000000000000000000000E-20"),
    wide_decimal_type("2.710505431213761085018632002174854278564453125000000000000000000000000000000000000000000000000000000E-20"),
    wide_decimal_type("5.421010862427522170037264004349708557128906250000000000000000000000000000000000000000000000000000000E-20"),
    wide_decimal_type("1.084202172485504434007452800869941711425781250000000000000000000000000000000000000000000000000000000E-19"),
    wide_decimal_type("2.168404344971008868014905601739883422851562500000000000000000000000000000000000000000000000000000000E-19"),
    wide_decimal_type("4.336808689942017736029811203479766845703125000000000000000000000000000000000000000000000000000000000E-19"),
    wide_decimal_type("8.673617379884035472059622406959533691406250000000000000000000000000000000000000000000000000000000000E-19"),
    wide_decimal_type("1.734723475976807094411924481391906738281250000000000000000000000000000000000000000000000000000000000E-18"),
    wide_decimal_type("3.469446951953614188823848962783813476562500000000000000000000000000000000000000000000000000000000000E-18"),
    wide_decimal_type("6.938893903907228377647697925567626953125000000000000000000000000000000000000000000000000000000000000E-18"),
    wide_decimal_type("1.387778780781445675529539585113525390625000000000000000000000000000000000000000000000000000000000000E-17"),
    wide_decimal_type("2.775557561562891351059079170227050781250000000000000000000000000000000000000000000000000000000000000E-17"),
    wide_decimal_type("5.551115123125782702118158340454101562500000000000000000000000000000000000000000000000000000000000000E-17"),
    wide_decimal_type("1.110223024625156540423631668090820312500000000000000000000000000000000000000000000000000000000000000E-16"),
    wide_decimal_type("2.220446049250313080847263336181640625000000000000000000000000000000000000000000000000000000000000000E-16"),
    wide_decimal_type("4.440892098500626161694526672363281250000000000000000000000000000000000000000000000000000000000000000E-16"),
    wide_decimal_type("8.881784197001252323389053344726562500000000000000000000000000000000000000000000000000000000000000000E-16"),
    wide_decimal_type("1.776356839400250464677810668945312500000000000000000000000000000000000000000000000000000000000000000E-15"),
    wide_decimal_type("3.552713678800500929355621337890625000000000000000000000000000000000000000000000000000000000000000000E-15"),
    wide_decimal_type("7.105427357601001858711242675781250000000000000000000000000000000000000000000000000000000000000000000E-15"),
    wide_decimal_type("1.421085471520200371742248535156250000000000000000000000000000000000000000000000000000000000000000000E-14"),
    wide_decimal_type("2.842170943040400743484497070312500000000000000000000000000000000000000000000000000000000000000000000E-14"),
    wide_decimal_type("5.684341886080801486968994140625000000000000000000000000000000000000000000000000000000000000000000000E-14"),
    wide_decimal_type("1.136868377216160297393798828125000000000000000000000000000000000000000000000000000000000000000000000E-13"),
    wide_decimal_type("2.273736754432320594787597656250000000000000000000000000000000000000000000000000000000000000000000000E-13"),
    wide_decimal_type("4.547473508864641189575195312500000000000000000000000000000000000000000000000000000000000000000000000E-13"),
    wide_decimal_type("9.094947017729282379150390625000000000000000000000000000000000000000000000000000000000000000000000000E-13"),
    wide_decimal_type("1.818989403545856475830078125000000000000000000000000000000000000000000000000000000000000000000000000E-12"),
    wide_decimal_type("3.637978807091712951660156250000000000000000000000000000000000000000000000000000000000000000000000000E-12"),
    wide_decimal_type("7.275957614183425903320312500000000000000000000000000000000000000000000000000000000000000000000000000E-12"),
    wide_decimal_type("1.455191522836685180664062500000000000000000000000000000000000000000000000000000000000000000000000000E-11"),
    wide_decimal_type("2.910383045673370361328125000000000000000000000000000000000000000000000000000000000000000000000000000E-11"),
    wide_decimal_type("5.820766091346740722656250000000000000000000000000000000000000000000000000000000000000000000000000000E-11"),
    wide_decimal_type("1.164153218269348144531250000000000000000000000000000000000000000000000000000000000000000000000000000E-10"),
    wide_decimal_type("2.328306436538696289062500000000000000000000000000000000000000000000000000000000000000000000000000000E-10"),
    wide_decimal_type("4.656612873077392578125000000000000000000000000000000000000000000000000000000000000000000000000000000E-10"),
    wide_decimal_type("9.313225746154785156250000000000000000000000000000000000000000000000000000000000000000000000000000000E-10"),
    wide_decimal_type("1.862645149230957031250000000000000000000000000000000000000000000000000000000000000000000000000000000E-9"),
    wide_decimal_type("3.725290298461914062500000000000000000000000000000000000000000000000000000000000000000000000000000000E-9"),
    wide_decimal_type("7.450580596923828125000000000000000000000000000000000000000000000000000000000000000000000000000000000E-9"),
    wide_decimal_type("1.490116119384765625000000000000000000000000000000000000000000000000000000000000000000000000000000000E-8"),
    wide_decimal_type("2.980232238769531250000000000000000000000000000000000000000000000000000000000000000000000000000000000E-8"),
    wide_decimal_type("5.960464477539062500000000000000000000000000000000000000000000000000000000000000000000000000000000000E-8"),
    wide_decimal_type("1.192092895507812500000000000000000000000000000000000000000000000000000000000000000000000000000000000E-7"),
    wide_decimal_type("2.384185791015625000000000000000000000000000000000000000000000000000000000000000000000000000000000000E-7"),
    wide_decimal_type("4.768371582031250000000000000000000000000000000000000000000000000000000000000000000000000000000000000E-7"),
    wide_decimal_type("9.536743164062500000000000000000000000000000000000000000000000000000000000000000000000000000000000000E-7"),
    wide_decimal_type("1.907348632812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000E-6"),
    wide_decimal_type("3.814697265625000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E-6"),
    wide_decimal_type("7.629394531250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E-6"),
    wide_decimal_type("0.00001525878906250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.00003051757812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.00006103515625000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.0001220703125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.0002441406250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.0004882812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.0009765625000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.001953125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.003906250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.007812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.01562500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.03125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.06250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.1250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.2500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("0.5000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("1.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("2.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("4.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("8.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("16.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("32.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("64.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("128.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("256.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("512.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("1024.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("2048.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("4096.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("8192.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("16384.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("32768.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("65536.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("131072.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("262144.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("524288.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    wide_decimal_type("1.048576000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E6"),
    wide_decimal_type("2.097152000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E6"),
    wide_decimal_type("4.194304000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E6"),
    wide_decimal_type("8.388608000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E6"),
    wide_decimal_type("1.677721600000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E7"),
    wide_decimal_type("3.355443200000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E7"),
    wide_decimal_type("6.710886400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E7"),
    wide_decimal_type("1.342177280000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E8"),
    wide_decimal_type("2.684354560000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E8"),
    wide_decimal_type("5.368709120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E8"),
    wide_decimal_type("1.073741824000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E9"),
    wide_decimal_type("2.147483648000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E9"),
    wide_decimal_type("4.294967296000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E9"),
    wide_decimal_type("8.589934592000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E9"),
    wide_decimal_type("1.717986918400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E10"),
    wide_decimal_type("3.435973836800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E10"),
    wide_decimal_type("6.871947673600000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E10"),
    wide_decimal_type("1.374389534720000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E11"),
    wide_decimal_type("2.748779069440000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E11"),
    wide_decimal_type("5.497558138880000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E11"),
    wide_decimal_type("1.099511627776000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E12"),
    wide_decimal_type("2.199023255552000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E12"),
    wide_decimal_type("4.398046511104000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E12"),
    wide_decimal_type("8.796093022208000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E12"),
    wide_decimal_type("1.759218604441600000000000000000000000000000000000000000000000000000000000000000000000000000000000000E13"),
    wide_decimal_type("3.518437208883200000000000000000000000000000000000000000000000000000000000000000000000000000000000000E13"),
    wide_decimal_type("7.036874417766400000000000000000000000000000000000000000000000000000000000000000000000000000000000000E13"),
    wide_decimal_type("1.407374883553280000000000000000000000000000000000000000000000000000000000000000000000000000000000000E14"),
    wide_decimal_type("2.814749767106560000000000000000000000000000000000000000000000000000000000000000000000000000000000000E14"),
    wide_decimal_type("5.629499534213120000000000000000000000000000000000000000000000000000000000000000000000000000000000000E14"),
    wide_decimal_type("1.125899906842624000000000000000000000000000000000000000000000000000000000000000000000000000000000000E15"),
    wide_decimal_type("2.251799813685248000000000000000000000000000000000000000000000000000000000000000000000000000000000000E15"),
    wide_decimal_type("4.503599627370496000000000000000000000000000000000000000000000000000000000000000000000000000000000000E15"),
    wide_decimal_type("9.007199254740992000000000000000000000000000000000000000000000000000000000000000000000000000000000000E15"),
    wide_decimal_type("1.801439850948198400000000000000000000000000000000000000000000000000000000000000000000000000000000000E16"),
    wide_decimal_type("3.602879701896396800000000000000000000000000000000000000000000000000000000000000000000000000000000000E16"),
    wide_decimal_type("7.205759403792793600000000000000000000000000000000000000000000000000000000000000000000000000000000000E16"),
    wide_decimal_type("1.441151880758558720000000000000000000000000000000000000000000000000000000000000000000000000000000000E17"),
    wide_decimal_type("2.882303761517117440000000000000000000000000000000000000000000000000000000000000000000000000000000000E17"),
    wide_decimal_type("5.764607523034234880000000000000000000000000000000000000000000000000000000000000000000000000000000000E17"),
    wide_decimal_type("1.152921504606846976000000000000000000000000000000000000000000000000000000000000000000000000000000000E18"),
    wide_decimal_type("2.305843009213693952000000000000000000000000000000000000000000000000000000000000000000000000000000000E18"),
    wide_decimal_type("4.611686018427387904000000000000000000000000000000000000000000000000000000000000000000000000000000000E18"),
    wide_decimal_type("9.223372036854775808000000000000000000000000000000000000000000000000000000000000000000000000000000000E18"),
    wide_decimal_type("1.844674407370955161600000000000000000000000000000000000000000000000000000000000000000000000000000000E19"),
    wide_decimal_type("3.689348814741910323200000000000000000000000000000000000000000000000000000000000000000000000000000000E19"),
    wide_decimal_type("7.378697629483820646400000000000000000000000000000000000000000000000000000000000000000000000000000000E19"),
    wide_decimal_type("1.475739525896764129280000000000000000000000000000000000000000000000000000000000000000000000000000000E20"),
    wide_decimal_type("2.951479051793528258560000000000000000000000000000000000000000000000000000000000000000000000000000000E20"),
    wide_decimal_type("5.902958103587056517120000000000000000000000000000000000000000000000000000000000000000000000000000000E20"),
    wide_decimal_type("1.180591620717411303424000000000000000000000000000000000000000000000000000000000000000000000000000000E21"),
    wide_decimal_type("2.361183241434822606848000000000000000000000000000000000000000000000000000000000000000000000000000000E21"),
    wide_decimal_type("4.722366482869645213696000000000000000000000000000000000000000000000000000000000000000000000000000000E21"),
    wide_decimal_type("9.444732965739290427392000000000000000000000000000000000000000000000000000000000000000000000000000000E21"),
    wide_decimal_type("1.888946593147858085478400000000000000000000000000000000000000000000000000000000000000000000000000000E22"),
    wide_decimal_type("3.777893186295716170956800000000000000000000000000000000000000000000000000000000000000000000000000000E22"),
    wide_decimal_type("7.555786372591432341913600000000000000000000000000000000000000000000000000000000000000000000000000000E22"),
    wide_decimal_type("1.511157274518286468382720000000000000000000000000000000000000000000000000000000000000000000000000000E23"),
    wide_decimal_type("3.022314549036572936765440000000000000000000000000000000000000000000000000000000000000000000000000000E23"),
    wide_decimal_type("6.044629098073145873530880000000000000000000000000000000000000000000000000000000000000000000000000000E23"),
    wide_decimal_type("1.208925819614629174706176000000000000000000000000000000000000000000000000000000000000000000000000000E24"),
    wide_decimal_type("2.417851639229258349412352000000000000000000000000000000000000000000000000000000000000000000000000000E24"),
    wide_decimal_type("4.835703278458516698824704000000000000000000000000000000000000000000000000000000000000000000000000000E24"),
    wide_decimal_type("9.671406556917033397649408000000000000000000000000000000000000000000000000000000000000000000000000000E24"),
    wide_decimal_type("1.934281311383406679529881600000000000000000000000000000000000000000000000000000000000000000000000000E25"),
    wide_decimal_type("3.868562622766813359059763200000000000000000000000000000000000000000000000000000000000000000000000000E25"),
    wide_decimal_type("7.737125245533626718119526400000000000000000000000000000000000000000000000000000000000000000000000000E25"),
    wide_decimal_type("1.547425049106725343623905280000000000000000000000000000000000000000000000000000000000000000000000000E26"),
    wide_decimal_type("3.094850098213450687247810560000000000000000000000000000000000000000000000000000000000000000000000000E26"),
    wide_decimal_type("6.189700196426901374495621120000000000000000000000000000000000000000000000000000000000000000000000000E26"),
    wide_decimal_type("1.237940039285380274899124224000000000000000000000000000000000000000000000000000000000000000000000000E27"),
    wide_decimal_type("2.475880078570760549798248448000000000000000000000000000000000000000000000000000000000000000000000000E27"),
    wide_decimal_type("4.951760157141521099596496896000000000000000000000000000000000000000000000000000000000000000000000000E27"),
    wide_decimal_type("9.903520314283042199192993792000000000000000000000000000000000000000000000000000000000000000000000000E27"),
    wide_decimal_type("1.980704062856608439838598758400000000000000000000000000000000000000000000000000000000000000000000000E28"),
    wide_decimal_type("3.961408125713216879677197516800000000000000000000000000000000000000000000000000000000000000000000000E28"),
    wide_decimal_type("7.922816251426433759354395033600000000000000000000000000000000000000000000000000000000000000000000000E28"),
    wide_decimal_type("1.584563250285286751870879006720000000000000000000000000000000000000000000000000000000000000000000000E29"),
    wide_decimal_type("3.169126500570573503741758013440000000000000000000000000000000000000000000000000000000000000000000000E29"),
    wide_decimal_type("6.338253001141147007483516026880000000000000000000000000000000000000000000000000000000000000000000000E29"),
    wide_decimal_type("1.267650600228229401496703205376000000000000000000000000000000000000000000000000000000000000000000000E30"),
    wide_decimal_type("2.535301200456458802993406410752000000000000000000000000000000000000000000000000000000000000000000000E30"),
    wide_decimal_type("5.070602400912917605986812821504000000000000000000000000000000000000000000000000000000000000000000000E30"),
    wide_decimal_type("1.014120480182583521197362564300800000000000000000000000000000000000000000000000000000000000000000000E31"),
    wide_decimal_type("2.028240960365167042394725128601600000000000000000000000000000000000000000000000000000000000000000000E31"),
    wide_decimal_type("4.056481920730334084789450257203200000000000000000000000000000000000000000000000000000000000000000000E31"),
    wide_decimal_type("8.112963841460668169578900514406400000000000000000000000000000000000000000000000000000000000000000000E31"),
    wide_decimal_type("1.622592768292133633915780102881280000000000000000000000000000000000000000000000000000000000000000000E32"),
    wide_decimal_type("3.245185536584267267831560205762560000000000000000000000000000000000000000000000000000000000000000000E32"),
    wide_decimal_type("6.490371073168534535663120411525120000000000000000000000000000000000000000000000000000000000000000000E32"),
    wide_decimal_type("1.298074214633706907132624082305024000000000000000000000000000000000000000000000000000000000000000000E33"),
    wide_decimal_type("2.596148429267413814265248164610048000000000000000000000000000000000000000000000000000000000000000000E33"),
    wide_decimal_type("5.192296858534827628530496329220096000000000000000000000000000000000000000000000000000000000000000000E33"),
    wide_decimal_type("1.038459371706965525706099265844019200000000000000000000000000000000000000000000000000000000000000000E34"),
    wide_decimal_type("2.076918743413931051412198531688038400000000000000000000000000000000000000000000000000000000000000000E34"),
    wide_decimal_type("4.153837486827862102824397063376076800000000000000000000000000000000000000000000000000000000000000000E34"),
    wide_decimal_type("8.307674973655724205648794126752153600000000000000000000000000000000000000000000000000000000000000000E34"),
    wide_decimal_type("1.661534994731144841129758825350430720000000000000000000000000000000000000000000000000000000000000000E35"),
    wide_decimal_type("3.323069989462289682259517650700861440000000000000000000000000000000000000000000000000000000000000000E35"),
    wide_decimal_type("6.646139978924579364519035301401722880000000000000000000000000000000000000000000000000000000000000000E35"),
    wide_decimal_type("1.329227995784915872903807060280344576000000000000000000000000000000000000000000000000000000000000000E36"),
    wide_decimal_type("2.658455991569831745807614120560689152000000000000000000000000000000000000000000000000000000000000000E36"),
    wide_decimal_type("5.316911983139663491615228241121378304000000000000000000000000000000000000000000000000000000000000000E36"),
    wide_decimal_type("1.063382396627932698323045648224275660800000000000000000000000000000000000000000000000000000000000000E37"),
    wide_decimal_type("2.126764793255865396646091296448551321600000000000000000000000000000000000000000000000000000000000000E37"),
    wide_decimal_type("4.253529586511730793292182592897102643200000000000000000000000000000000000000000000000000000000000000E37"),
    wide_decimal_type("8.507059173023461586584365185794205286400000000000000000000000000000000000000000000000000000000000000E37"),
    wide_decimal_type("1.701411834604692317316873037158841057280000000000000000000000000000000000000000000000000000000000000E38"),
  }};

  bool result_is_ok = true;

  wide_decimal_type local_half(wide_decimal_type(1U) / 2U);
  wide_decimal_type local_one (1U);
  wide_decimal_type local_two (2U);

  for(auto i = static_cast<std::ptrdiff_t>(0); i < static_cast<std::ptrdiff_t>(local_pow2_data.size()); ++i)
  {
    wide_decimal_type x2;

    if(i <= static_cast<std::ptrdiff_t>(INT32_C(127)))
    {
      x2 = pow(local_half, static_cast<std::ptrdiff_t>(static_cast<std::ptrdiff_t>(std::tuple_size<local_pow2_data_type>::value / 2U) - i));
    }
    else if(i == static_cast<std::ptrdiff_t>(std::tuple_size<local_pow2_data_type>::value / 2U))
    {
      x2 = local_one;
    }
    else
    {
      x2 = pow(local_two, static_cast<std::ptrdiff_t>(i - static_cast<std::ptrdiff_t>(std::tuple_size<local_pow2_data_type>::value / 2U)));
    }

    result_is_ok &= (x2 == local_pow2_data[static_cast<std::size_t>(i)]); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
  }

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = math::wide_decimal::example001d_pow2_from_list();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif
