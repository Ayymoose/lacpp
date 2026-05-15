#pragma once

#include <array>
#include <string_view>

namespace zelda::core
{

class Messages
{
public:
    enum Id : int
    {
        MSG_0,   // Dialog000 – Tarin
        MSG_1,   // Dialog001 – Marin
        MSG_2,   // Dialog002 – Marin
        MSG_3,   // Dialog003 – Marin
        MSG_4,   // Dialog004 – Marin
        MSG_5,   // Dialog005 – Marin
        MSG_6,   // Dialog006 – Marin
        MSG_7,   // Dialog007 – Narrator
        MSG_8,   // Dialog008 – Narrator
        MSG_9,   // Dialog009 – Witch
        MSG_10,  // Dialog00A – Tarin
        MSG_11,  // Dialog00B – Tarin
        MSG_12,  // Dialog00C – Witch
        MSG_13,  // Dialog00D – Tarin
        MSG_14,  // Dialog00E – Narrator
        MSG_15,  // Dialog00F – Narrator
        MSG_16,  // Dialog010 – Tarin
        MSG_17,  // Dialog011 – Tarin
        MSG_18,  // Dialog012 – Talking Tree
        MSG_19,  // Dialog013 – Narrator
        MSG_20,  // Dialog014 – Marin
        MSG_21,  // Dialog015 – Marin
        MSG_22,  // Dialog016 – Marin
        MSG_23,  // Dialog017 – Crazy Tracy
        MSG_24,  // Dialog018 – Crazy Tracy
        MSG_25,  // Dialog019 – Crazy Tracy
        MSG_26,  // Dialog01A – Crazy Tracy
        MSG_27,  // Dialog01B – Crazy Tracy
        MSG_28,  // Dialog01C – Crazy Tracy
        MSG_29,  // Dialog01D – Crazy Tracy
        MSG_30,  // Dialog01E – Crazy Tracy
        MSG_31,  // Dialog01F – Narrator
        MSG_32,  // Dialog020 – Mutt
        MSG_33,  // Dialog021 – Tarin
        MSG_34,  // Dialog022 – BowWow
        MSG_35,  // Dialog023 – ChowChow
        MSG_36,  // Dialog024 – Great Fairy
        MSG_37,  // Dialog025 – Grim Creeper (D7 Mini-Boss)
        MSG_38,  // Dialog026 – Grim Creeper (D7 Mini-Boss)
        MSG_39,  // Dialog027 – Papahl
        MSG_40,  // Dialog028 – Marin
        MSG_41,  // Dialog029 – Shopkeeper
        MSG_42,  // Dialog02A – Narrator
        MSG_43,  // Dialog02B – Shopkeeper, Link
        MSG_44,  // Dialog02C – Shopkeeper, Link
        MSG_45,  // Dialog02D – Shopkeeper, Link
        MSG_46,  // Dialog02E – Shopkeeper
        MSG_47,  // Dialog02F – Shopkeeper
        MSG_48,  // Dialog030 – Shopkeeper, Link
        MSG_49,  // Dialog031 – Shopkeeper, Link
        MSG_50,  // Dialog032 – Shopkeeper, Link
        MSG_51,  // Dialog033 – Shopkeeper, Link
        MSG_52,  // Dialog034 – Shopkeeper
        MSG_53,  // Dialog035 – Shopkeeper
        MSG_54,  // Dialog036 – Narrator
        MSG_55,  // Dialog037 – Shopkeeper
        MSG_56,  // Dialog038 – Shopkeeper
        MSG_57,  // Dialog039 – Narrator
        MSG_58,  // Dialog03A – Trendy Gamester
        MSG_59,  // Dialog03B – Trendy Gamester
        MSG_60,  // Dialog03C – Trendy Gamester
        MSG_61,  // Dialog03D – Narrator
        MSG_62,  // Dialog03E – Trendy Gamester, Link
        MSG_63,  // Dialog03F – Trendy Gamester
        MSG_64,  // Dialog040 – Trendy Gamester
        MSG_65,  // Dialog041 – Narrator
        MSG_66,  // Dialog042 – Trendy Gamester, probably
        MSG_67,  // Dialog043 – Ghost
        MSG_68,  // Dialog044 – Narrator
        MSG_69,  // Dialog045 – Fisherman
        MSG_70,  // Dialog046 – Fisherman
        MSG_71,  // Dialog047 – Fisherman
        MSG_72,  // Dialog048 – Fisherman, Link
        MSG_73,  // Dialog049 – Fisherman, Link
        MSG_74,  // Dialog04A – Fisherman, Link
        MSG_75,  // Dialog04B – Fisherman, Link
        MSG_76,  // Dialog04C – Fisherman, Link
        MSG_77,  // Dialog04D – Fisherman, Link
        MSG_78,  // Dialog04E – Fisherman
        MSG_79,  // Dialog04F – Narrator
        MSG_80,  // Dialog050 – Narrator
        MSG_81,  // Dialog051 – Narrator
        MSG_82,  // Dialog052 – Genie (D2 Nightmare)
        MSG_83,  // Dialog053 – Genie (D2 Nightmare)
        MSG_84,  // Dialog054 – Tarin
        MSG_85,  // Dialog055 – Tarin
        MSG_86,  // Dialog056 – Map
        MSG_87,  // Dialog057 – Map
        MSG_88,  // Dialog058 – Map
        MSG_89,  // Dialog059 – Map
        MSG_90,  // Dialog05A – Map
        MSG_91,  // Dialog05B – Map
        MSG_92,  // Dialog05C – Map
        MSG_93,  // Dialog05D – Map
        MSG_94,  // Dialog05E – Map
        MSG_95,  // Dialog05F – Map
        MSG_96,  // Dialog060 – Map
        MSG_97,  // Dialog061 – Map
        MSG_98,  // Dialog062 – Map
        MSG_99,  // Dialog063 – Map
        MSG_100, // Dialog064 – Map
        MSG_101, // Dialog065 – Map
        MSG_102, // Dialog066 – Map
        MSG_103, // Dialog067 – Map
        MSG_104, // Dialog068 – Map
        MSG_105, // Dialog069 – Map
        MSG_106, // Dialog06A – Map
        MSG_107, // Dialog06B – Map
        MSG_108, // Dialog06C – Map
        MSG_109, // Dialog06D – Map
        MSG_110, // Dialog06E – Map
        MSG_111, // Dialog06F – Map
        MSG_112, // Dialog070 – Map
        MSG_113, // Dialog071 – Map
        MSG_114, // Dialog072 – Map
        MSG_115, // Dialog073 – Map
        MSG_116, // Dialog074 – Map
        MSG_117, // Dialog075 – Map
        MSG_118, // Dialog076 – Map
        MSG_119, // Dialog077 – Map
        MSG_120, // Dialog078 – Map
        MSG_121, // Dialog079 – Map
        MSG_122, // Dialog07A – Map
        MSG_123, // Dialog07B – Map
        MSG_124, // Dialog07C – Map
        MSG_125, // Dialog07D – Map
        MSG_126, // Dialog07E – Map
        MSG_127, // Dialog07F – Map
        MSG_128, // Dialog080 – Map
        MSG_129, // Dialog081 – Map
        MSG_130, // Dialog082 – Map
        MSG_131, // Dialog083 – Signpost
        MSG_132, // Dialog084 – Map
        MSG_133, // Dialog085 – Map
        MSG_134, // Dialog086 – Map
        MSG_135, // Dialog087 – Map
        MSG_136, // Dialog088 – Map
        MSG_137, // Dialog089 – Map
        MSG_138, // Dialog08A – Narrator
        MSG_139, // Dialog08B – Narrator
        MSG_140, // Dialog08C – Narrator
        MSG_141, // Dialog08D – Narrator
        MSG_142, // Dialog08E – Narrator
        MSG_143, // Dialog08F – Marin
        MSG_144, // Dialog090 – Narrator
        MSG_145, // Dialog091 – Narrator
        MSG_146, // Dialog092 – Desert skull
        MSG_147, // Dialog093 – Narrator
        MSG_148, // Dialog094 – Narrator
        MSG_149, // Dialog095 – Narrator
        MSG_150, // Dialog096 – Narrator
        MSG_151, // Dialog097 – Narrator
        MSG_152, // Dialog098 – Narrator
        MSG_153, // Dialog099 – Narrator
        MSG_154, // Dialog09A – Narrator
        MSG_155, // Dialog09B – Narrator
        MSG_156, // Dialog09C – Narrator
        MSG_157, // Dialog09D – Narrator
        MSG_158, // Dialog09E – Narrator
        MSG_159, // Dialog09F – Narrator
        MSG_160, // Dialog0A0 – Narrator
        MSG_161, // Dialog0A1 – Narrator
        MSG_162, // Dialog0A2 – Narrator
        MSG_163, // Dialog0A3 – Narrator
        MSG_164, // Dialog0A4 – Narrator
        MSG_165, // Dialog0A5 – Narrator
        MSG_166, // Dialog0A6 – Narrator
        MSG_167, // Dialog0A7 – Narrator
        MSG_168, // Dialog0A8 – Narrator
        MSG_169, // Dialog0A9 – Narrator
        MSG_170, // Dialog0AA – Narrator
        MSG_171, // Dialog0AB – Narrator
        MSG_172, // Dialog0AC – Narrator
        MSG_173, // Dialog0AD – Narrator
        MSG_174, // Dialog0AE – Narrator
        MSG_175, // Dialog0AF – Hippo
        MSG_176, // Dialog0B0 – Moldorm (D1 Nightmare)
        MSG_177, // Dialog0B1 – Slime Eyes (D3 Nightmare)
        MSG_178, // Dialog0B2 – Angler Fish (D4 Nightmare)
        MSG_179, // Dialog0B3 – Slime Eel (D5 Nightmare)
        MSG_180, // Dialog0B4 – Genie (D2 Nightmare)
        MSG_181, // Dialog0B5 – Slime Eel (D5 Nightmare)
        MSG_182, // Dialog0B6 – Facade (D6 Nightmare)
        MSG_183, // Dialog0B7 – Facade (D6 Nightmare)
        MSG_184, // Dialog0B8 – Grim Creeper (D7 Nightmare)
        MSG_185, // Dialog0B9 – Grim Creeper (D7 Nightmare)
        MSG_186, // Dialog0BA – Grim Creeper (D7 Nightmare)
        MSG_187, // Dialog0BB – Hot Head (D8 Nightmare)
        MSG_188, // Dialog0BC – Hot Head (D8 Nightmare)
        MSG_189, // Dialog0BD – Hot Head (D8 Nightmare)
        MSG_190, // Dialog0BE – Owl
        MSG_191, // Dialog0BF – Owl
        MSG_192, // Dialog0C0 – Owl
        MSG_193, // Dialog0C1 – Owl
        MSG_194, // Dialog0C2 – Owl
        MSG_195, // Dialog0C3 – Owl
        MSG_196, // Dialog0C4 – Owl
        MSG_197, // Dialog0C5 – Owl
        MSG_198, // Dialog0C6 – Owl
        MSG_199, // Dialog0C7 – Owl
        MSG_200, // Dialog0C8 – Owl
        MSG_201, // Dialog0C9 – Owl
        MSG_202, // Dialog0CA – Owl
        MSG_203, // Dialog0CB – Owl
        MSG_204, // Dialog0CC – Owl
        MSG_205, // Dialog0CD – Owl
        MSG_206, // Dialog0CE – Owl
        MSG_207, // Dialog0CF – Owl
        MSG_208, // Dialog0D0 – Wind Fish
        MSG_209, // Dialog0D1 – Wind Fish
        MSG_210, // Dialog0D2 – Wind Fish
        MSG_211, // Dialog0D3 – Map, probably
        MSG_212, // Dialog0D4 – Map, probably
        MSG_213, // Dialog0D5 – Map, probably
        MSG_214, // Dialog0D6 – Owl
        MSG_215, // Dialog0D7 – Owl
        MSG_216, // Dialog0D8 – Schule Donavitch
        MSG_217, // Dialog0D9 – Owl
        MSG_218, // Dialog0DA – Lanmola
        MSG_219, // Dialog0DB – Mamu
        MSG_220, // Dialog0DC – Mamu
        MSG_221, // Dialog0DD – Mamu
        MSG_222, // Dialog0DE – Mamu
        MSG_223, // Dialog0DF – Narrator
        MSG_224, // Dialog0E0 – Mamu
        MSG_225, // Dialog0E1 – Li'l Devil
        MSG_226, // Dialog0E2 – Li'l Devil
        MSG_227, // Dialog0E3 – Li'l Devil
        MSG_228, // Dialog0E4 – Li'l Devil
        MSG_229, // Dialog0E5 – Li'l Devil
        MSG_230, // Dialog0E6 – Narrator
        MSG_231, // Dialog0E7 – Southern Face Shrine mural
        MSG_232, // Dialog0E8 – Narrator
        MSG_233, // Dialog0E9 – Narrator
        MSG_234, // Dialog0EA – Narrator
        MSG_235, // Dialog0EB – Narrator
        MSG_236, // Dialog0EC – Narrator
        MSG_237, // Dialog0ED – Narrator
        MSG_238, // Dialog0EE – Narrator
        MSG_239, // Dialog0EF – Narrator
        MSG_240, // Dialog0F0 – Raft Guy
        MSG_241, // Dialog0F1 – Raft Guy
        MSG_242, // Dialog0F2 – Signpost, probably
        MSG_243, // Dialog0F3 – Signpost, probably
        MSG_244, // Dialog0F4 – Signpost, probably
        MSG_245, // Dialog0F5 – Nightmare (final boss)
        MSG_246, // Dialog0F6 – Nightmare (final boss)
        MSG_247, // Dialog0F7 – Marin
        MSG_248, // Dialog0F8 – Marin
        MSG_249, // Dialog0F9 – Trendy Gamester
        MSG_250, // Dialog0FA – Hippo
        MSG_251, // Dialog0FB – idk
        MSG_252, // Dialog0FC – Narrator
        MSG_253, // Dialog0FD – Narrator
        MSG_254, // Dialog0FE – Witch
        MSG_255, // Dialog0FF – Tarin
        MSG_256, // Dialog100 – Narrator
        MSG_257, // Dialog101 – Narrator
        MSG_258, // Dialog102 – Narrator
        MSG_259, // Dialog103 – Narrator
        MSG_260, // Dialog104 – Narrator
        MSG_261, // Dialog105 – Narrator
        MSG_262, // Dialog106 – Narrator
        MSG_263, // Dialog107 – Narrator
        MSG_264, // Dialog108 – Photographer
        MSG_265, // Dialog109 – Photographer
        MSG_266, // Dialog10A – Photographer, probably
        MSG_267, // Dialog10B – Photographer
        MSG_268, // Dialog10C – Photographer
        MSG_269, // Dialog10D – Photographer
        MSG_270, // Dialog10E – Photographer
        MSG_271, // Dialog10F – Photographer
        MSG_272, // Dialog110 – Narrator
        MSG_273, // Dialog111 – Master Stalfos (D5 Mini-Boss)
        MSG_274, // Dialog112 – Master Stalfos (D5 Mini-Boss)
        MSG_275, // Dialog113 – Master Stalfos (D5 Mini-Boss)
        MSG_276, // Dialog114 – Master Stalfos (D5 Mini-Boss)
        MSG_277, // Dialog115 – BowWow
        MSG_278, // Dialog116 – Narrator
        MSG_279, // Dialog117 – idk
        MSG_280, // Dialog118 – Kid
        MSG_281, // Dialog119 – Kid
        MSG_282, // Dialog11A – Kid
        MSG_283, // Dialog11B – Kid
        MSG_284, // Dialog11C – Kid
        MSG_285, // Dialog11D – Kid
        MSG_286, // Dialog11E – Kid
        MSG_287, // Dialog11F – Kid
        MSG_288, // Dialog120 – Kid
        MSG_289, // Dialog121 – Kid
        MSG_290, // Dialog122 – Kid
        MSG_291, // Dialog123 – Kid, probably
        MSG_292, // Dialog124 – Fisherman
        MSG_293, // Dialog125 – Fisherman
        MSG_294, // Dialog126 – Zora
        MSG_295, // Dialog127 – Mamasha
        MSG_296, // Dialog128 – Mamasha, probably
        MSG_297, // Dialog129 – Narrator
        MSG_298, // Dialog12A – Mamasha
        MSG_299, // Dialog12B – Mamasha
        MSG_300, // Dialog12C – Mamasha
        MSG_301, // Dialog12D – Richard
        MSG_302, // Dialog12E – Photographer
        MSG_303, // Dialog12F – Madam MeowMeow
        MSG_304, // Dialog130 – Madam MeowMeow
        MSG_305, // Dialog131 – Madam MeowMeow
        MSG_306, // Dialog132 – Madam MeowMeow
        MSG_307, // Dialog133 – Weird Mr. Write
        MSG_308, // Dialog134 – Weird Mr. Write
        MSG_309, // Dialog135 – Weird Mr. Write
        MSG_310, // Dialog136 – Narrator
        MSG_311, // Dialog137 – Weird Mr. Write
        MSG_312, // Dialog138 – Weird Mr. Write
        MSG_313, // Dialog139 – Weird Mr. Write
        MSG_314, // Dialog13A – Richard
        MSG_315, // Dialog13B – Richard
        MSG_316, // Dialog13C – Richard
        MSG_317, // Dialog13D – Richard
        MSG_318, // Dialog13E – Richard
        MSG_319, // Dialog13F – Richard
        MSG_320, // Dialog140 – Ulrira, Narrator
        MSG_321, // Dialog141 – Ulrira
        MSG_322, // Dialog142 – Ulrira
        MSG_323, // Dialog143 – Ulrira
        MSG_324, // Dialog144 – Ulrira
        MSG_325, // Dialog145 – Ulrira
        MSG_326, // Dialog146 – Ulrira
        MSG_327, // Dialog147 – Ulrira
        MSG_328, // Dialog148 – Ulrira
        MSG_329, // Dialog149 – Ulrira
        MSG_330, // Dialog14A – Ulrira
        MSG_331, // Dialog14B – Ulrira
        MSG_332, // Dialog14C – Ulrira
        MSG_333, // Dialog14D – Ulrira
        MSG_334, // Dialog14E – Ulrira
        MSG_335, // Dialog14F – Ulrira
        MSG_336, // Dialog150 – Wind Fish, probably
        MSG_337, // Dialog151 – Wind Fish, probably
        MSG_338, // Dialog152 – Wind Fish, probably
        MSG_339, // Dialog153 – Wind Fish, probably
        MSG_340, // Dialog154 – Wind Fish, probably
        MSG_341, // Dialog155 – Wind Fish, probably
        MSG_342, // Dialog156 – Wind Fish, probably
        MSG_343, // Dialog157 – Wind Fish, probably
        MSG_344, // Dialog158 – Grandma Yahoo
        MSG_345, // Dialog159 – Grandma Yahoo
        MSG_346, // Dialog15A – Grandma Yahoo
        MSG_347, // Dialog15B – Grandma Yahoo
        MSG_348, // Dialog15C – Grandma Yahoo
        MSG_349, // Dialog15D – Grandma Yahoo
        MSG_350, // Dialog15E – Narrator
        MSG_351, // Dialog15F – Grandma Yahoo
        MSG_352, // Dialog160 – Kiki
        MSG_353, // Dialog161 – Kiki
        MSG_354, // Dialog162 – Kiki
        MSG_355, // Dialog163 – Kiki
        MSG_356, // Dialog164 – Narrator
        MSG_357, // Dialog165 – Kiki, Narrator, Link
        MSG_358, // Dialog166 – Christine
        MSG_359, // Dialog167 – Christine
        MSG_360, // Dialog168 – Christine
        MSG_361, // Dialog169 – Christine
        MSG_362, // Dialog16A – Narrator
        MSG_363, // Dialog16B – Christine
        MSG_364, // Dialog16C – Narrator
        MSG_365, // Dialog16D – Narrator
        MSG_366, // Dialog16E – Ulrira
        MSG_367, // Dialog16F – Kid, probably
        MSG_368, // Dialog170 – Papahl
        MSG_369, // Dialog171 – Papahl
        MSG_370, // Dialog172 – Papahl
        MSG_371, // Dialog173 – Papahl
        MSG_372, // Dialog174 – Narrator
        MSG_373, // Dialog175 – Papahl
        MSG_374, // Dialog176 – Papahl, probably
        MSG_375, // Dialog177 – Papahl
        MSG_376, // Dialog178 – Grandma Yahoo
        MSG_377, // Dialog179 – Spirit of the Mansion
        MSG_378, // Dialog17A – Narrator
        MSG_379, // Dialog17B – Spirit of the Mansion
        MSG_380, // Dialog17C – idk, might be unused?
        MSG_381, // Dialog17D – Map, probably
        MSG_382, // Dialog17E – Witch
        MSG_383, // Dialog17F – Genie (D2 Nightmare)
        MSG_384, // Dialog180 – CiaoCiao
        MSG_385, // Dialog181 – CiaoCiao, Link
        MSG_386, // Dialog182 – Narrator
        MSG_387, // Dialog183 – CiaoCiao
        MSG_388, // Dialog184 – CiaoCiao
        MSG_389, // Dialog185 – Manbo
        MSG_390, // Dialog186 – Manbo
        MSG_391, // Dialog187 – Manbo
        MSG_392, // Dialog188 – Narrator
        MSG_393, // Dialog189 – Manbo
        MSG_394, // Dialog18A – Manbo
        MSG_395, // Dialog18B – Henhouse Keeper
        MSG_396, // Dialog18C – Henhouse Keeper
        MSG_397, // Dialog18D – Henhouse Keeper
        MSG_398, // Dialog18E – Weathervane
        MSG_399, // Dialog18F – Schule Donavitch
        MSG_400, // Dialog190 – Moblin
        MSG_401, // Dialog191 – Moblin Chief
        MSG_402, // Dialog192 – Marin
        MSG_403, // Dialog193 – Marin
        MSG_404, // Dialog194 – Marin
        MSG_405, // Dialog195 – Marin
        MSG_406, // Dialog196 – Mutt, narrator
        MSG_407, // Dialog197 – Marin
        MSG_408, // Dialog198 – Marin
        MSG_409, // Dialog199 – Marin
        MSG_410, // Dialog19A – Crazy Tracy
        MSG_411, // Dialog19B – Schule Donavitch
        MSG_412, // Dialog19C – Mermaid Statue, Narrator
        MSG_413, // Dialog19D – Signpost and maybe ; Map
        MSG_414, // Dialog19E – Signpost, probably
        MSG_415, // Dialog19F – Signpost
        MSG_416, // Dialog1A0 – Signpost
        MSG_417, // Dialog1A1 – Signpost, probably
        MSG_418, // Dialog1A2 – Signpost
        MSG_419, // Dialog1A3 – Signpost and maybe ; Map
        MSG_420, // Dialog1A4 – Signpost
        MSG_421, // Dialog1A5 – Signpost
        MSG_422, // Dialog1A6 – Signpost
        MSG_423, // Dialog1A7 – Signpost and maybe ; Map
        MSG_424, // Dialog1A8 – Signpost
        MSG_425, // Dialog1A9 – Signpost
        MSG_426, // Dialog1AA – Signpost
        MSG_427, // Dialog1AB – Signpost
        MSG_428, // Dialog1AC – Signpost
        MSG_429, // Dialog1AD – Signpost
        MSG_430, // Dialog1AE – Signpost
        MSG_431, // Dialog1AF – Signpost
        MSG_432, // Dialog1B0 – Signpost
        MSG_433, // Dialog1B1 – Signpost
        MSG_434, // Dialog1B2 – Signpost
        MSG_435, // Dialog1B3 – Signpost
        MSG_436, // Dialog1B4 – Signpost
        MSG_437, // Dialog1B5 – Signpost
        MSG_438, // Dialog1B6 – Owl Statue
        MSG_439, // Dialog1B7 – Owl Statue
        MSG_440, // Dialog1B8 – Owl Statue
        MSG_441, // Dialog1B9 – Owl Statue
        MSG_442, // Dialog1BA – Owl Statue
        MSG_443, // Dialog1BB – Owl Statue
        MSG_444, // Dialog1BC – Owl Statue
        MSG_445, // Dialog1BD – Owl Statue
        MSG_446, // Dialog1BE – Owl Statue
        MSG_447, // Dialog1BF – Tarin
        MSG_448, // Dialog1C0 – Tarin
        MSG_449, // Dialog1C1 – Narrator
        MSG_450, // Dialog1C2 – Marin, probably
        MSG_451, // Dialog1C3 – Signpost
        MSG_452, // Dialog1C4 – Tarin
        MSG_453, // Dialog1C5 – Tarin
        MSG_454, // Dialog1C6 – Sale
        MSG_455, // Dialog1C7 – Sale
        MSG_456, // Dialog1C8 – Sale
        MSG_457, // Dialog1C9 – Sale
        MSG_458, // Dialog1CA – Sale
        MSG_459, // Dialog1CB – Narrator
        MSG_460, // Dialog1CC – Sale
        MSG_461, // Dialog1CD – Sale
        MSG_462, // Dialog1CE – Chef Bear
        MSG_463, // Dialog1CF – Chef Bear
        MSG_464, // Dialog1D0 – Narrator
        MSG_465, // Dialog1D1 – Chef Bear, probably
        MSG_466, // Dialog1D2 – Chef Bear
        MSG_467, // Dialog1D3 – Chef Bear
        MSG_468, // Dialog1D4 – Chef Bear
        MSG_469, // Dialog1D5 – Marin
        MSG_470, // Dialog1D6 – Marin
        MSG_471, // Dialog1D7 – Marin
        MSG_472, // Dialog1D8 – Marin
        MSG_473, // Dialog1D9 – Marin
        MSG_474, // Dialog1DA – Marin, Link
        MSG_475, // Dialog1DB – Marin
        MSG_476, // Dialog1DC – Marin
        MSG_477, // Dialog1DD – Tarin
        MSG_478, // Dialog1DE – Marin
        MSG_479, // Dialog1DF – idk
        MSG_480, // Dialog1E0 – Walrus
        MSG_481, // Dialog1E1 – Marin, Link
        MSG_482, // Dialog1E2 – Marin
        MSG_483, // Dialog1E3 – Marin
        MSG_484, // Dialog1E4 – Marin
        MSG_485, // Dialog1E5 – Marin, probably
        MSG_486, // Dialog1E6 – idk
        MSG_487, // Dialog1E7 – Fisherman
        MSG_488, // Dialog1E8 – Fisherman
        MSG_489, // Dialog1E9 – Fisherman
        MSG_490, // Dialog1EA – Fisherman
        MSG_491, // Dialog1EB – Fisherman
        MSG_492, // Dialog1EC – Narrator
        MSG_493, // Dialog1ED – Fisherman
        MSG_494, // Dialog1EE – Mamasha
        MSG_495, // Dialog1EF – Secret Zora
        MSG_496, // Dialog1F0 – Mermaid
        MSG_497, // Dialog1F1 – Mermaid
        MSG_498, // Dialog1F2 – Mermaid
        MSG_499, // Dialog1F3 – Mermaid
        MSG_500, // Dialog1F4 – Mermaid
        MSG_501, // Dialog1F5 – Narrator
        MSG_502, // Dialog1F6 – Photographer
        MSG_503, // Dialog1F7 – Mermaid
        MSG_504, // Dialog1F8 – Photographer
        MSG_505, // Dialog1F9 – Signpost maybe, and ; Map maybe
        MSG_506, // Dialog1FA – Signpost
        MSG_507, // Dialog1FB – Signpost
        MSG_508, // Dialog1FC – Signpost
        MSG_509, // Dialog1FD – Bucket Mouse
        MSG_510, // Dialog1FE – Fisherman, Link
        MSG_511, // Dialog1FF – Fisherman, Link
        MSG_512, // Dialog200 – Book, Narrator
        MSG_513, // Dialog201 – Book
        MSG_514, // Dialog202 – Book, Narrator
        MSG_515, // Dialog203 – Book
        MSG_516, // Dialog204 – Book, Narrator
        MSG_517, // Dialog205 – Book, Narrator
        MSG_518, // Dialog206 – Book, Narrator
        MSG_519, // Dialog207 – Book
        MSG_520, // Dialog208 – Book, Narrator
        MSG_521, // Dialog209 – Book
        MSG_522, // Dialog20A – Book, Narrator
        MSG_523, // Dialog20B – Book
        MSG_524, // Dialog20C – Book, Narrator
        MSG_525, // Dialog20D – Book, Narrator
        MSG_526, // Dialog20E – Book, Narrator
        MSG_527, // Dialog20F – Ghost
        MSG_528, // Dialog210 – Ghost
        MSG_529, // Dialog211 – Ghost
        MSG_530, // Dialog212 – Ghost
        MSG_531, // Dialog213 – Ghost
        MSG_532, // Dialog214 – Ghost
        MSG_533, // Dialog215 – Ghost
        MSG_534, // Dialog216 – Ghost
        MSG_535, // Dialog217 – Book, Narrator
        MSG_536, // Dialog218 – Book, Narrator
        MSG_537, // Dialog219 – Book, Narrator
        MSG_538, // Dialog21A – Book, Narrator
        MSG_539, // Dialog21B – Marin
        MSG_540, // Dialog21C – Marin
        MSG_541, // Dialog21D – Marin
        MSG_542, // Dialog21E – Marin
        MSG_543, // Dialog21F – Kid
        MSG_544, // Dialog220 – Kid
        MSG_545, // Dialog221 – Secret Goriya
        MSG_546, // Dialog222 – Secret Goriya
        MSG_547, // Dialog223 – Secret Goriya
        MSG_548, // Dialog224 – Narrator
        MSG_549, // Dialog225 – Secret Goriya, Link
        MSG_550, // Dialog226 – Narrator
        MSG_551, // Dialog227 – Secret Goriya
        MSG_552, // Dialog228 – Ulrira
        MSG_553, // Dialog229 – Ulrira
        MSG_554, // Dialog22A – Ulrira
        MSG_555, // Dialog22B – Photo Album, Narrator
        MSG_556, // Dialog22C – Narrator
        MSG_557, // Dialog22D – Signpost, probably
        MSG_558, // Dialog22E – Photographer
        MSG_559, // Dialog22F – Narrator
        MSG_560, // Dialog230 – Narrator
        MSG_561, // Dialog231 – Narrator
        MSG_562, // Dialog232 – Narrator
        MSG_563, // Dialog233 – Narrator
        MSG_564, // Dialog234 – Narrator
        MSG_565, // Dialog235 – Marin
        MSG_566, // Dialog236 – Marin
        MSG_567, // Dialog237 – Marin
        MSG_568, // Dialog238 – Marin
        MSG_569, // Dialog239 – Marin
        MSG_570, // Dialog23A – Marin
        MSG_571, // Dialog23B – Tarin
        MSG_572, // Dialog23C – Richard
        MSG_573, // Dialog23D – Tarin
        MSG_574, // Dialog23E – Photographer, probably
        MSG_575, // Dialog23F – Photographer, probably
        MSG_576, // Dialog240 – Ulrira
        MSG_577, // Dialog241 – Ulrira
        MSG_578, // Dialog242 – Ulrira
        MSG_579, // Dialog243 – Ulrira
        MSG_580, // Dialog244 – Ulrira
        MSG_581, // Dialog245 – Ulrira
        MSG_582, // Dialog246 – Ulrira
        MSG_583, // Dialog247 – Ulrira
        MSG_584, // Dialog248 – Ulrira
        MSG_585, // Dialog249 – idk
        MSG_586, // Dialog24A – idk
        MSG_587, // Dialog24B – idk
        MSG_588, // Dialog24C – idk
        MSG_589, // Dialog24D – idk
        MSG_590, // Dialog24E – idk
        MSG_591, // Dialog24F – idk
        MSG_592, // Dialog250 – idk
        MSG_593, // Dialog251 – Rabbit
        MSG_594, // Dialog252 – idk
        MSG_595, // Dialog253 – idk
        MSG_596, // Dialog254 – idk
        MSG_597, // Dialog255 – Marin
        MSG_598, // Dialog256 – Marin
        MSG_599, // Dialog257 – Marin
        MSG_600, // Dialog258 – Marin
        MSG_601, // Dialog259 – Photographer, maybe
        MSG_602, // Dialog25A – Narrator
        MSG_603, // Dialog25B – Narrator
        MSG_604, // Dialog25C – Fairy Queen (Color Dungeon)
        MSG_605, // Dialog25D – Fairy Queen (Color Dungeon), Link
        MSG_606, // Dialog25E – Dion (Color Dungeon)
        MSG_607, // Dialog25F – Gar (Color Dungeon)
        MSG_608, // Dialog260 – Color Guard (Color Dungeon)
        MSG_609, // Dialog261 – idk
        MSG_610, // Dialog262 – Color Guard (Color Dungeon)
        MSG_611, // Dialog263 – idk (Color Dungeon)
        MSG_612, // Dialog264 – idk
        MSG_613, // Dialog265 – idk
        MSG_614, // Dialog266 – Narrator
        MSG_615, // Dialog267 – Book, Narrator
        MSG_616, // Dialog268 – Fairy Queen (Color Dungeon)
        MSG_617, // Dialog269 – idk
        MSG_618, // Dialog26A – idk
        MSG_619, // Dialog26B – Great Fairy
        MSG_620, // Dialog26C – idk (Color Dungeon)
        MSG_621, // Dialog26D – idk (Color Dungeon)
        MSG_622, // Dialog26E – idk (Color Dungeon)
        MSG_623, // Dialog26F – idk (Color Dungeon)
        MSG_624, // Dialog270 – Photographer
        MSG_625, // Dialog271 – BowWow
        MSG_626, // Dialog272 – Photographer
        MSG_627, // Dialog273 – BowWow
        MSG_628, // Dialog274 – Photographer
        MSG_629, // Dialog275 – BowWow
        MSG_630, // Dialog276 – Marin
        MSG_631, // Dialog277 – Marin
        MSG_632, // Dialog278 – Marin
        MSG_633, // Dialog279 – Marin
        MSG_634, // Dialog27A – Marin, probably
        MSG_635, // Dialog27B – Marin, probably
        MSG_636, // Dialog27C – Cukeman
        MSG_637, // Dialog27D – Cukeman
        MSG_638, // Dialog27E – Cukeman
        MSG_639, // Dialog27F – Cukeman
        MSG_640, // Dialog280 – Owl Statue
        MSG_641, // Dialog281 – Owl Statue
        MSG_642, // Dialog282 – Owl Statue
        MSG_643, // Dialog283 – Owl Statue
        MSG_644, // Dialog284 – Owl Statue
        MSG_645, // Dialog285 – Owl Statue
        MSG_646, // Dialog286 – Owl Statue
        MSG_647, // Dialog287 – Owl Statue
        MSG_648, // Dialog288 – Owl Statue
        MSG_649, // Dialog289 – Owl Statue
        MSG_650, // Dialog28A – Owl Statue
        MSG_651, // Dialog28B – Owl Statue
        MSG_652, // Dialog28C – Owl Statue
        MSG_653, // Dialog28D – Owl Statue
        MSG_654, // Dialog28E – Owl Statue
        MSG_655, // Dialog28F – Owl Statue
        MSG_656, // Dialog290 – Owl Statue
        MSG_657, // Dialog291 – Owl Statue
        MSG_658, // Dialog292 – Owl Statue
        MSG_659, // Dialog293 – Owl Statue
        MSG_660, // Dialog294 – Photographer, Link
        MSG_661, // Dialog295 – Photographer, Link
        MSG_662, // Dialog296 – Photographer
        MSG_663, // Dialog297 – Photographer
        MSG_664, // Dialog298 – Photographer
        MSG_665, // Dialog299 – Photographer
        MSG_666, // Dialog29A – Photographer
        MSG_667, // Dialog29B – Photographer
        MSG_668, // Dialog29C – Photographer
        MSG_669, // Dialog29D – Photographer
        MSG_670, // Dialog29E – Photographer
        MSG_671, // Dialog29F – Photographer
        MSG_672, // Dialog2A0 – Photographer
        MSG_673, // Dialog2A1 – Photographer
        MSG_674, // Dialog2A2 – Photographer
        MSG_675, // Dialog2A3 – Photographer
        MSG_676, // Dialog2A4 – Photographer
        MSG_677, // Dialog2A5 – Photographer
        MSG_678, // Dialog2A6 – Photographer
        MSG_679, // Dialog2A7 – Photographer
        MSG_680, // Dialog2A8 – Photographer
        MSG_681, // Dialog2A9 – Photographer
        MSG_682, // Dialog2AA – Photographer
        MSG_683, // Dialog2AB – Photographer
        MSG_684, // Dialog2AC – Photographer, probably
        MSG_685, // Dialog2AD – Photographer, probably
        MSG_686, // Dialog2AE – Photographer, probably
        MSG_687, // Dialog2AF – Photographer, probably

        // Credits
        // NewStaffRoles
        MSG_688, // 1998 STAFF
        MSG_689, // SUPERVISOR
        MSG_690, // DIRECTOR
        MSG_691, // SCRIPT WRITER
        MSG_692, // PROGRAMMER
        MSG_693, // CHARACTER DESIGNER
        MSG_694, // SOUND COMPOSER
        MSG_695, // ART WORK
        MSG_696, // TECHNICAL SUPPORT
        MSG_697, // ENGLISH SCRIPT
        MSG_698, // SPECIAL THANKS TO

        // DebugStaffRoles
        MSG_699, // DEBUG STAFF

        // OriginalStaffRoles
        MSG_700, // 1993 STAFF
        MSG_701, // DUNGEON DESIGNER
        MSG_702, // ILLUSTRATOR
        MSG_703, // PRODUCER
        MSG_704, // EXECUTIVE PRODUCER
        MSG_705, //

        // NewStaffPeople
        MSG_706, //
        MSG_707, // TAKASHI TEZUKA
        MSG_708, // YOSINORI TUTIYAMA
        MSG_709, // NOBUO MATSUMIYA
        MSG_710, // EIJI NOTO
        MSG_711, // KIYOSHI KODA
        MSG_712, // SIGEHIRO KASAMATU
        MSG_713, // MIKIO MISHIMA
        MSG_714, // KYOKO KIMURA
        MSG_715, // YUICHI OZAKI
        MSG_716, // KEIKO IZAWA
        MSG_717, // N KOGANEZAWA
        MSG_718, // JIM WORNELL
        MSG_719, // KEIKO TAMURA
        MSG_720, // TAMAYO ITO
        MSG_721, // AKIYA SAKAMOTO
        MSG_722, // R&D2 DEBUG STAFF
        MSG_723, // SUPER MARIO CLUB
        MSG_724, // YASUHISA YAMAMURA
        MSG_725, // KENSUKE TANABE
        MSG_726, // YOSHIAKI KOIZUMI
        MSG_727, // KAZUAKI MORITA
        MSG_728, // TAKAMITSU KUZUHARA
        MSG_729, // MASANAO ARIMOTO
        MSG_730, // SHIGEFUMI HINO
        MSG_731, // KAZUMI TOTAKA
        MSG_732, // MINAKO HAMANO
        MSG_733, // KOZUE ISHIKAWA
        MSG_734, // YOUICHI KOTABE
        MSG_735, // DAN OWSEN
        MSG_736, // TOSHIHIKO NAKAGO
        MSG_737, // KOJI KONDO
        MSG_738, // TOMOAKI KUROUME
        MSG_739, // MASAICHI OKUMURA
        MSG_740, // KANAE WADA
        MSG_741, // SHIGERU MIYAMOTO
        MSG_742, // HIROSHI YAMAUCHI
        MSG_743, // THE  END
        COUNT
    };

    [[nodiscard]] static constexpr std::string_view get(Id id) { return m_messages[id]; }

    static constexpr std::array<std::string_view, COUNT> m_messages = {{
        "Whoa, boy! Whereya off to in    such a hurry?   Set a spell, I  got somethin' tatell ya!", // MSG_0 – Dialog000
                                                                                                    // – Tarin
        "What a relief! I thought you'd   never wake up!  You were tossing and turning...  What?  Zelda?   No, my name's "
        "  Marin!  You must still be feelinga little woozy. You are on      Koholint Island!", // MSG_1 – Dialog001 –
                                                                                              // Marin
        "Follow the lane south to reach  the beach where I found you.    Since you washedashore, lots of nasty "
        "monsters  have been in thearea, so be     careful, okay?", // MSG_2 – Dialog002 – Marin
        "Hi!  Tarin went to the forest tolook for toad-  stools, but I'd rather sing.    Listen to this, it's called "
        "the 'Ballad of the  Wind Fish.'",                                               // MSG_3 – Dialog003 – Marin
        "Hey!  That's a  nice Ocarina youhave there! Willyou accompany   me as I sing?", // MSG_4 – Dialog004 – Marin
        "I just love to  sing-- what can I say?  What do you like to do, #####?",        // MSG_5 – Dialog005 – Marin
        "#####, Tarin's  taking a nap at home.  I don't  know how he can sleep on such a nice day!  It   makes me want "
        "tosing a song...  Yes, the song is'Ballad of the  Wind Fish!'",                // MSG_6 – Dialog006 – Marin
        "Eh? It's locked!You can open thedoor with the   Nightmare Key.",               // MSG_7 – Dialog007 – Narrator
        "You got a Piece of Power!  You  can feel the    energy flowing  through you!", // MSG_8 – Dialog008 – Narrator
        "Ahhh... It has  the Sleepy Toad-stool, it does! We'll mix it up something in a  jiffy, we will!", // MSG_9 –
                                                                                                           // Dialog009
                                                                                                           // – Witch
        "The last thing Ikin remember wasbitin' into a   big juicy toad- stool... Then, Ihad the darndestdream... I "
        "was araccoon!  Yeah, sounds strange, but it sure was fun!",                     // MSG_10 – Dialog00A – Tarin
        "I'm all tucker'dout...  I think I better set a  spell before I  head home...",  // MSG_11 – Dialog00B – Tarin
        "Double double,  toil and troublea toadstool mix makes powder fortricks!",       // MSG_12 – Dialog00C – Witch
        "As a raccoon, mynose is verrry  sensitive, ta   stuff like dust and powder...", // MSG_13 – Dialog00D – Tarin
        "It's the toad-  stool you pickedin the woods.   What is it for? You hold it overyour head and a mellow aroma  "
        "  wafts into your nostrils.", // MSG_14 – Dialog00E – Narrator
        "You pick the    toadstool... As you hold it overyour head, a    mellow aroma    flows into your nostrils.", // MSG_15 – Dialog00F – Narrator
        "Hrrrm...Snore...Hunh?... If'n yadon' know...callold man Ulrira! Zonk...Snore...", // MSG_16 – Dialog010 – Tarin
        "I'm tired... I'mgoin' ta sleep  now... Zzzzzz...",                                // MSG_17 – Dialog011 – Tarin
        "Well that was a surprise!  Hey! I'll tell you a secret! Use yoursword to poke atdungeon walls...If you hear a "
        "  hollow clank,   you can break   the wall with a Bomb!", // MSG_18 – Dialog012 – Talking Tree
        "You've learned  the 'Ballad of  the Wind Fish!' This song will  always remain inyour heart!", // MSG_19 –
                                                                                                       // Dialog013 –
                                                                                                       // Narrator
        "Please remember this song!  You should play it  every once in a while to keep itfresh in your   mind!", // MSG_20
                                                                                                                 // –
                                                                                                                 // Dialog014
                                                                                                                 // –
                                                                                                                 // Marin
        "Please!  I want you to learn it!This song is my favorite!", // MSG_21 – Dialog015 – Marin
        "So, how do you  like it?  It's  really touching,isn't it?  Does it stick in yourmind?               Yes  "
        "No<ask>", // MSG_22 – Dialog016 – Marin
        "Hi there, big   guy!  I'm Crazy Tracy!  I've gota little secret for sale that'llpump you up!", // MSG_23 –
                                                                                                        // Dialog017 –
                                                                                                        // Crazy Tracy
        "Will you give me28 Rupees for mysecret?             Give Don't<ask>", // MSG_24 – Dialog018 – Crazy Tracy
        "How about it?   42 Rupees for mylittle secret...    Give Don't<ask>", // MSG_25 – Dialog019 – Crazy Tracy
        "All right, come here and I'll   rub it on you!  ...There... I'veapplied my own  secret medicine!It will take  "
        "  effect when you lose all hearts!lose all heart! Drop by again,  big guy!", // MSG_26 – Dialog01A – Crazy Tracy
        "Beat it, then!  Come back when  you have some   cash!", // MSG_27 – Dialog01B – Crazy Tracy
        "... ... ... ... But I won't sellit to you!",            // MSG_28 – Dialog01C – Crazy Tracy
        "Well!  I'm only offering you a  secret that willmake you strong!You're such a   chicken!!", // MSG_29 –
                                                                                                     // Dialog01D –
                                                                                                     // Crazy Tracy
        "...You're so    cute!  I'll giveyou a 7 Rupee   discount!",        // MSG_30 – Dialog01E – Crazy Tracy
        "You got Marin!  Is this your bigchance?",                          // MSG_31 – Dialog01F – Narrator
        "GRRRR...",                                                         // MSG_32 – Dialog020 – Mutt
        "Heh heh heh ho! You're goin' ta be lost, thanks to me!  Heh heh!", // MSG_33 – Dialog021 – Tarin
        "BOW WOW!        BOW WOW!",                                         // MSG_34 – Dialog022 – BowWow
        "YIP YIP!        YIP YIP!",                                         // MSG_35 – Dialog023 – ChowChow
        "Let's heal your wounds and get  rid of all that stress... Close your eyes and   relax...", // MSG_36 – Dialog024
                                                                                                    // – Great Fairy
        "You dirty rat!  You k-k-k...beatmy brothers!    You'll pay!!    I'll never      forget you!", // MSG_37 –
                                                                                                       // Dialog025 –
                                                                                                       // Grim Creeper
                                                                                                       // (D7 Mini-Boss)
        "Hey runt!  You  think you can   take me?!  All  right boys, get this punk out   of my face!", // MSG_38 –
                                                                                                       // Dialog026 –
                                                                                                       // Grim Creeper
                                                                                                       // (D7 Mini-Boss)
        "Yep!  Those're  my boys!  I'm   Papahl, pleased ta meetcha! I'llbe lost in the  hills later, so keep a look "
        "out for me, hear?", // MSG_39 – Dialog027 – Papahl
        "Yes!!  Yes!!    Break them!     Break them all! ... ... ... ... What?  What's   wrong?", // MSG_40 – Dialog028
                                                                                                  // – Marin
        "Aye Caramba!    Kid, you have a lot to learn,   trying to buy   something you   have no use for!", // MSG_41 –
                                                                                                            // Dialog029
                                                                                                            // –
                                                                                                            // Shopkeeper
        "You've got a    Heart!  Thump!  One of your     Heart Containersis filled!", // MSG_42 – Dialog02A – Narrator
        "Bow & Arrow Set Only 980 Rupees!    Buy  No Way<ask>",           // MSG_43 – Dialog02B – Shopkeeper, Link
        "Bow & Arrow Set Only 980 Rupees!    Buy  No Way<ask>",           // MSG_44 – Dialog02C – Shopkeeper, Link
        "   10 Arrows       10 Rupees        Buy  Don't<ask>",            // MSG_45 – Dialog02D – Shopkeeper, Link
        "Hey!  Welcome!  See something   you like?!  Justbring it here!", // MSG_46 – Dialog02E – Shopkeeper
        "Hey! You! Stop! You gotta pay!  Put it back!",                   // MSG_47 – Dialog02F – Shopkeeper
        "  Deluxe Shovel    200 Rupees!  Seems expensive!    Buy  No Way!<ask>", // MSG_48 – Dialog030 – Shopkeeper, Link
        "   Three Hearts     10 Rupees!      Buy  Don't<ask>", // MSG_49 – Dialog031 – Shopkeeper, Link
        "     Shield         20 Rupees!      Buy  Don't<ask>", // MSG_50 – Dialog032 – Shopkeeper, Link
        "    Ten Bombs       10 Rupees       Buy  Don't<ask>", // MSG_51 – Dialog033 – Shopkeeper, Link
        "Sorry, kid!  Youdon't have the  Rupees!  Come   back when you   have the cash!", // MSG_52 – Dialog034 –
                                                                                          // Shopkeeper
        "Thanks a lot!   And come again!",                                         // MSG_53 – Dialog035 – Shopkeeper
        "Guess what?  Yougot it for free.Are you proud ofyourself?",               // MSG_54 – Dialog036 – Narrator
        "I wasn't kiddingwhen I said pay!Now, you'll pay the ultimate    price!!", // MSG_55 – Dialog037 – Shopkeeper
        "I wasn't kiddingwhen I said pay!Now, you'll pay the ultimate    price!!", // MSG_56 – Dialog038 – Shopkeeper
        "Hunh?  It soundslike the castle gate opened! Youcan easily leavethe castle now!", // MSG_57 – Dialog039 –
                                                                                           // Narrator
        "  TRENDY GAME!   One Play 10 Rs.    Play No<ask>", // MSG_58 – Dialog03A – Trendy Gamester
        "  TRENDY GAME!   One Play 10 Rs.    Play No<ask>", // MSG_59 – Dialog03B – Trendy Gamester
        "The A and B     Buttons move thecrane...The restis just timing! Go over to the  buttons to play!Good Luck!", // MSG_60 – Dialog03C – Trendy Gamester
        "It's a Shield!  There is space  for your name!",  // MSG_61 – Dialog03D – Narrator
        "Challenge Again?    Play No<ask>",                // MSG_62 – Dialog03E – Trendy Gamester, Link
        "Good Luck!",                                      // MSG_63 – Dialog03F – Trendy Gamester
        "We're closing upfor today!  Comeagain, anytime!", // MSG_64 – Dialog040 – Trendy Gamester
        "You got some    Magic Powder!   Try to sprinkle it on many      things!", // MSG_65 – Dialog041 – Narrator
        "It's 30 Rupees! You can play thegame three more times with this!", // MSG_66 – Dialog042 – Trendy Gamester,
                                                                            // probably
        "Cough Cough...  Don't sprinkle  that on me...   ...I'll have to curse you!      Cough Cough...", // MSG_67 –
                                                                                                          // Dialog043 –
                                                                                                          // Ghost
        "You got a Yoshi Doll!  Recently,he seems to be  showing up in   many games!", // MSG_68 – Dialog044 – Narrator
        "How about some  fishing, little buddy? I'll onlycharge you 10   Rupees...           Fish Not Now<ask>", // MSG_69
                                                                                                                 // –
                                                                                                                 // Dialog045
                                                                                                                 // –
                                                                                                                 // Fisherman
        "You have to havemore passion!   Live a little!", // MSG_70 – Dialog046 – Fisherman
        "Okay, here's howyou do it.  Use <left> and <right> on the <dpad>to aim a cast.  Once you hook a fish, press "
        "the Button rapidly  to reel him in!",                                   // MSG_71 – Dialog047 – Fisherman
        "Why not try one more time,      little buddy?       Cast Not Now<ask>", // MSG_72 – Dialog048 – Fisherman, Link
        "Wow! That one   got away!  Want to try again?       Cast Not Now<ask>", // MSG_73 – Dialog049 – Fisherman, Link
        "Wow! Nice Fish! It's a lunker!! I'll give you a 20 Rupee prize! Try again?          Cast Not Now<ask>", // MSG_74
                                                                                                                 // –
                                                                                                                 // Dialog04A
                                                                                                                 // –
                                                                                                                 // Fisherman,
                                                                                                                 // Link
        "This pond's all fished out.  Whynot try your    luck in the sea?    Okay No<ask>", // MSG_75 – Dialog04B –
                                                                                            // Fisherman, Link
        "Did I say that? Forget it, okay?Run along now...", // MSG_76 – Dialog04C – Fisherman, Link
        "It's a runt!    I'll only give  you a 5 Rupees  prize for that. You should try  again!              Okay "
        "No<ask>", // MSG_77 – Dialog04D – Fisherman, Link
        "You're short of Rupees?  Don't  worry about it. You just come   back when you   have more money,little buddy.", // MSG_78 – Dialog04E – Fisherman
        "You've got a    Piece of Heart! Press SELECT on the Subscreen   to see.", // MSG_79 – Dialog04F – Narrator
        "You collected   four Pieces of  Heart.  Now, youhave a complete Heart Container!", // MSG_80 – Dialog050 –
                                                                                            // Narrator
        "Brrrr... This isa block of solidice!  It's very cold!",      // MSG_81 – Dialog051 – Narrator
        "NYAH NYAH! You  can't hurt me aslong as I have  my bottle!", // MSG_82 – Dialog052 – Genie (D2 Nightmare)
        "Waaaah! You- youbroke my bottle!Why, you... You make me hopping mad!!!", // MSG_83 – Dialog053 – Genie (D2
                                                                                  // Nightmare)
        "Well, #####, ya finally snapped out of it...    Name's Tarin... Hope yer feelin'better...  What?How did I "
        "know  your name?  You think it's weirdeh?  Well, I sawit on the back  of this shield!it on back of   this "
        "shield!", // MSG_84 – Dialog054 – Tarin
        "Oh, yeah... Someother stuff likethis washed up  on the beach... If'n you go lookwatch out for   monsters! "
        "Ever  since you showedup, #####, I've seen 'em all    over the place!", // MSG_85 – Dialog055 – Tarin
        "Level 1--            Tail Cave",                                        // MSG_86 – Dialog056 – Map
        "Level 2--          Bottle Grotto",                                      // MSG_87 – Dialog057 – Map
        "Level 3--             Key Cavern",                                      // MSG_88 – Dialog058 – Map
        "Level 4--        Angler's Tunnel",                                      // MSG_89 – Dialog059 – Map
        "Level 5--          Catfish's Maw",                                      // MSG_90 – Dialog05A – Map
        "Level 6--            Face Shrine",                                      // MSG_91 – Dialog05B – Map
        "Level 7--          Eagle's Tower",                                      // MSG_92 – Dialog05C – Map
        "Level 8--            Turtle Rock",                                      // MSG_93 – Dialog05D – Map
        "Wind Fish's Egg ",                                                      // MSG_94 – Dialog05E – Map
        "Mountain Bridge ",                                                      // MSG_95 – Dialog05F – Map
        "Mountain Bridge ",                                                      // MSG_96 – Dialog060 – Map
        "Sale's House O'     Bananas",                                           // MSG_97 – Dialog061 – Map
        "Pothole Field",                                                         // MSG_98 – Dialog062 – Map
        "    House By         The Bay",                                          // MSG_99 – Dialog063 – Map
        "   Trendy Game",                                                        // MSG_100 – Dialog064 – Map
        "  Town Tool Shop",                                                      // MSG_101 – Dialog065 – Map
        "Marin and          Tarin's House",                                      // MSG_102 – Dialog066 – Map
        "   Witch's Hut",                                                        // MSG_103 – Dialog067 – Map
        "  Yarna Desert",                                                        // MSG_104 – Dialog068 – Map
        "  Ukuku Prairie",                                                       // MSG_105 – Dialog069 – Map
        "Mysterious Woods",                                                      // MSG_106 – Dialog06A – Map
        "  Mt. Tamaranch ",                                                      // MSG_107 – Dialog06B – Map
        "     Tal Tal     Mountain Range ",                                      // MSG_108 – Dialog06C – Map
        "  Signpost Maze ",                                                      // MSG_109 – Dialog06D – Map
        "  Mabe Village  ",                                                      // MSG_110 – Dialog06E – Map
        " Animal Village ",                                                      // MSG_111 – Dialog06F – Map
        "    Cemetery    ",                                                      // MSG_112 – Dialog070 – Map
        "   Rapids Ride  ",                                                      // MSG_113 – Dialog071 – Map
        "Koholint Prairie",                                                      // MSG_114 – Dialog072 – Map
        " Toronbo Shores",                                                       // MSG_115 – Dialog073 – Map
        "  Martha's Bay",                                                        // MSG_116 – Dialog074 – Map
        "East of the Bay",                                                       // MSG_117 – Dialog075 – Map
        "  Goponga Swamp",                                                       // MSG_118 – Dialog076 – Map
        "   Face Shrine ",                                                       // MSG_119 – Dialog077 – Map
        " Kanalet Castle",                                                       // MSG_120 – Dialog078 – Map
        "Tal Tal Heights",                                                       // MSG_121 – Dialog079 – Map
        "Tabahl Wasteland",                                                      // MSG_122 – Dialog07A – Map
        "  South of the      Village",                                           // MSG_123 – Dialog07B – Map
        "  Fishing Pond  ",                                                      // MSG_124 – Dialog07C – Map
        "Madam MeowMeow's     House       Beware of Dog!",                       // MSG_125 – Dialog07D – Map
        "Old Man Ulrira's     House      ",                                      // MSG_126 – Dialog07E – Map
        "Weird Mr. Write ",                                                      // MSG_127 – Dialog07F – Map
        " Crazy Tracy's    Health Spa",                                          // MSG_128 – Dialog080 – Map
        "Quadruplet's          House",                                           // MSG_129 – Dialog081 – Map
        "  Dream Shrine  ",                                                      // MSG_130 – Dialog082 – Map
        "Telephone Booth <down> Signpost Maze ",                                 // MSG_131 – Dialog083 – Signpost
        "Seashell Mansion",                                                      // MSG_132 – Dialog084 – Map
        "Richard's Villa ",                                                      // MSG_133 – Dialog085 – Map
        "     Hen House  ",                                                      // MSG_134 – Dialog086 – Map
        "Village Library ",                                                      // MSG_135 – Dialog087 – Map
        "    Raft Shop   ",                                                      // MSG_136 – Dialog088 – Map
        "    Warp Hole   ",                                                      // MSG_137 – Dialog089 – Map
        "This rock has   many cracks...  There must be   some way to     shatter it...", // MSG_138 – Dialog08A –
                                                                                         // Narrator
        "Oh? What a weirdobject!  There  must be some wayto tackle this  obstacle.", // MSG_139 – Dialog08B – Narrator
        "Hunh?  This rockhas a key hole! You should come back with a key!",          // MSG_140 – Dialog08C – Narrator
        "Wow!  This lookspretty heavy!   You won't be    able to lift it with just your  bare hands...", // MSG_141 –
                                                                                                         // Dialog08D –
                                                                                                         // Narrator
        "Well, it's an   Ocarina, but youdon't know how  to play it...",           // MSG_142 – Dialog08E – Narrator
        "No!  No!  Poor  hen!  Stop that!",                                        // MSG_143 – Dialog08F – Marin
        "You found the   Power Bracelet! At last, you canpick up pots andstones!", // MSG_144 – Dialog090 – Narrator
        "You got your    shield back!    Press the buttonand repel       enemies with it!", // MSG_145 – Dialog091 –
                                                                                            // Narrator
        "Ahhh... Yess... That dust was sorefreshing...   For that, I'll  tell you a hint!Use a Bomb in a place where "
        "the sand swallows   you... There is a treat on the  other side of   the wall... Bye!", // MSG_146 – Dialog092 –
                                                                                                // Desert skull
        "You've got the  Hook Shot!  Its chain stretches long when you   use it!", // MSG_147 – Dialog093 – Narrator
        "You've got the  Magic Rod!  Now you can burn    things! Burn it!Burn, baby burn!", // MSG_148 – Dialog094 –
                                                                                            // Narrator
        "You've got the  Pegasus Boots!  If you hold downthe Button, you can dash!", // MSG_149 – Dialog095 – Narrator
        "You've got the  Ocarina!  You   should learn to play many songs!",          // MSG_150 – Dialog096 – Narrator
        "You've got the  Roc's Feather!  It feels like   your body is a  lot lighter!", // MSG_151 – Dialog097 – Narrator
        "You've got a    Shovel!  Now youcan feel the joyof digging!",                // MSG_152 – Dialog098 – Narrator
        "You've got some Magic Powder!   Try sprinkling  it on a variety of things!", // MSG_153 – Dialog099 – Narrator
        "You've got a    bomb! Way to    go!",                                        // MSG_154 – Dialog09A – Narrator
        "You found your  Sword!  It must be yours becauseit has your nameengraved on it!", // MSG_155 – Dialog09B –
                                                                                           // Narrator
        "You've got the  Flippers! If youpress the B     Button while youswim, you can   dive underwater!", // MSG_156 –
                                                                                                            // Dialog09C
                                                                                                            // – Narrator
        "You've got the  Magnifying Lens!This will revealmany things you couldn't see    before!", // MSG_157 – Dialog09D
                                                                                                   // – Narrator
        "You've got a    new Sword!  You should put your name on it rightaway!", // MSG_158 – Dialog09E – Narrator
        "You've got a    new Sword!  You should put your name on it rightaway!", // MSG_159 – Dialog09F – Narrator
        "You found the   secret medicine!You should applythis and see    what happens!", // MSG_160 – Dialog0A0 –
                                                                                         // Narrator
        "You've got the  Tail Key!  Now  you can open theTail Cave gate!",          // MSG_161 – Dialog0A1 – Narrator
        "You've got the  Slime Key!  Now you can open thegate in Ukuku   Prairie!", // MSG_162 – Dialog0A2 – Narrator
        "You've got the  Angler Key!",                                              // MSG_163 – Dialog0A3 – Narrator
        "You've got the  Face Key!",                                                // MSG_164 – Dialog0A4 – Narrator
        "You've got the  Bird Key!",                                                // MSG_165 – Dialog0A5 – Narrator
        "At last, you gota Map!  Press   the START Buttonto look at it!",           // MSG_166 – Dialog0A6 – Narrator
        "You've got the  Compass!  Now,  you can see     where the chestsand Nightmare   are hidden! ThisCompass has a "
        "  new feature-- a tone will tell  you if a key is hidden in a roomwhen you enter! ", // MSG_167 – Dialog0A7 –
                                                                                              // Narrator
        "You found a     stone beak!     Let's find the  owl statue that belongs to it.", // MSG_168 – Dialog0A8 –
                                                                                          // Narrator
        "You've got the  Nightmare's Key!Now you can openthe door to the Nightmare's     Lair!", // MSG_169 – Dialog0A9
                                                                                                 // – Narrator
        "You got a Small Key!  You can   open a locked   door.", // MSG_170 – Dialog0AA – Narrator
        "   You got 20        Rupees!          JOY!",            // MSG_171 – Dialog0AB – Narrator
        "    You got 50        Rupees!       Very Nice!",        // MSG_172 – Dialog0AC – Narrator
        "   You got 100       Rupees!      You're Happy!",       // MSG_173 – Dialog0AD – Narrator
        "   You got 200       Rupees!    You're Ecstatic!",      // MSG_174 – Dialog0AE – Narrator
        "Leave me alone! I'm trying to   sit still so    Schule can paintmy portrait!", // MSG_175 – Dialog0AF – Hippo
        "BUZZZZZ! BUZZZZ!   OUTZZZIDER!  ",                // MSG_176 – Dialog0B0 – Moldorm (D1 Nightmare)
        "NEENER NEENER!  You can't find  me!  NYAH NYAH!", // MSG_177 – Dialog0B1 – Slime Eyes (D3 Nightmare)
        "BLOOOP! BLOOOP!   GLUB!  GLUB!  OGGGH!  FOOOOD! BLOOOOP!  GLUB!", // MSG_178 – Dialog0B2 – Angler Fish (D4
                                                                           // Nightmare)
        "Ssso...you are  the outsssider, come to wake theWind Fisssh...  KEEE-HEE-HEEEH! I shall eat you!", // MSG_179 –
                                                                                                            // Dialog0B3
                                                                                                            // – Slime
                                                                                                            // Eel (D5
                                                                                                            // Nightmare)
        "HO HO HO!       I'm your bad guythis time!!     HO HO HO!", // MSG_180 – Dialog0B4 – Genie (D2 Nightmare)
        "TSSSK, TSSSK!   You don't ssseemto know what    kind of island  thisss iss...   KEEE-HEEE-HEEE! What a "
        "fool...  KEE-HEE-HEH!!", // MSG_181 – Dialog0B5 – Slime Eel (D5 Nightmare)
        "Hey dummy! Need a hint?  My weakpoint is... !!  Whoops!  There Igo, talking too much again...", // MSG_182 –
                                                                                                         // Dialog0B6 –
                                                                                                         // Facade (D6
                                                                                                         // Nightmare)
        "Okay, listen up!If the Wind Fishwakes up, every-thing on this   island will be  gone forever!   And I do "
        "mean...EVERYTHING!", // MSG_183 – Dialog0B7 – Facade (D6 Nightmare)
        "My energy...    gone...I...lost!But you will be lost too, if theWind Fish wakes!Same as "
        "me...you...are...in...  his...dream...", // MSG_184 – Dialog0B8 – Grim Creeper (D7 Nightmare)
        "My energy...    gone...I...lost!But you will be lost too, if theWind Fish wakes!Same as "
        "me...you...are...in...  his...dream...", // MSG_185 – Dialog0B9 – Grim Creeper (D7 Nightmare)
        "BAH!  I'm not   going to hold   back!  I'm goingto make you wishyou were never  born!!", // MSG_186 – Dialog0BA
                                                                                                  // – Grim Creeper (D7
                                                                                                  // Nightmare)
        "CRACKLE-FWOOOSH!You're finished!I will never letyou play the    Instruments of  the Sirens!!", // MSG_187 –
                                                                                                        // Dialog0BB –
                                                                                                        // Hot Head (D8
                                                                                                        // Nightmare)
        "CRACKLE-FWOOOSH!You're finished!I will never letyou play the    Instruments of  the Sirens!!", // MSG_188 –
                                                                                                        // Dialog0BC –
                                                                                                        // Hot Head (D8
                                                                                                        // Nightmare)
        "C-C-CRACKLE!    Why did you comehere?  If it    weren't for you,nothing would   have to change! You cannot "
        "wake the Wind Fish!  Remember, you...too...are in... ...the dream...", // MSG_189 – Dialog0BD – Hot Head (D8
                                                                                // Nightmare)
        "Hoot!  Ho, bravelad, on your    quest to wake   the dreamer!    Welcome to the  Mysterious Wood!Much of "
        "mystery you will find onthis uncharted  Koholint island!I'm afraid you  may find it a   trifle difficultto "
        "leave the    island while theWind Fish naps. ...By the by,   have you ever   visited the TailCave, which is  "
        "south of the    village?  Go    there with the  key you find in this forest...  The Wind Fish "
        "iswatching...Hoot!", // MSG_190 – Dialog0BE – Owl
        "Hoot!  Ho, bravelad, on your    quest to wake   the dreamer!    Welcome to the  Mysterious Wood!Much of "
        "mystery you will find onthis uncharted  Koholint island!I'm afraid you  may find it a   trifle difficultto "
        "leave the    island while theWind Fish naps. ...By the by,   have you ever   visited the TailCave, which is  "
        "south of the    village?  Go    there with the  key you find in this forest...  The Wind Fish "
        "iswatching...Hoot!", // MSG_191 – Dialog0BF – Owl
        "Hoot!  Ho, bravelad, on your    quest to wake   the dreamer!    Welcome to the  Mysterious Wood!Much of "
        "mystery you will find onthis uncharted  Koholint island!I'm afraid you  may find it a   trifle difficultto "
        "leave the    island while theWind Fish naps. ...By the by,   have you ever   visited the TailCave, which is  "
        "south of the    village?  Go    there with the  key you find in this forest...  The Wind Fish "
        "iswatching...Hoot!", // MSG_192 – Dialog0C0 – Owl
        "Hoot!  Take the key and go to   the Tail Cave.  Retrieve the    Instrument that is hidden there!Go now!  The  "
        "  Wind Fish is    waiting!  Hooot!", // MSG_193 – Dialog0C1 – Owl
        "Hoooot!  That isan 'Instrument  of the Sirens!' I have to admit,at first I did  not believe you were real...  "
        "  That Instrument,along with the  seven others in the set, has thepower to wake   the Wind Fish!  You must "
        "collectthem all!  I wasinstructed to   give you direc- tions...  Your  next goal is    north, in       "
        "Goponga Swamp!! Hoot, indeed!", // MSG_194 – Dialog0C2 – Owl
        "Hoot!  That is afearsome lookinganimal you have there!  Do not  forget, the nextInstrument is inGoponga "
        "Swamp!", // MSG_195 – Dialog0C3 – Owl
        "Hoooot! The WindFish sleeps longand dreamily in the Egg above...When you play   the eight Siren Instruments "
        "in  front of the Egghe will awaken. This, my friend,is the only way for you to leavethe island! Hoo!", // MSG_196
                                                                                                                // –
                                                                                                                // Dialog0C4
                                                                                                                // – Owl
        "Hoot!  How many Instruments     have you gotten so far?  When   you play the    Instruments in  front of the  "
        "  Egg, the Wind   Fish will wake  and you will    leave this      island.  Now,   you must hasten to the "
        "Yarna    Desert!  The    dark, monstrous inhabitants of  the sand will   show you the    way! Hoot Hoot!", // MSG_197 – Dialog0C5 – Owl
        "Hoot!  The shapeof the key showsa fish, swimmingup a cascade of water!  Go now  to the mountain waterfall!  A "
        "  leap from the   top and you willreach your goal!", // MSG_198 – Dialog0C6 – Owl
        "Hoot!  There aretwo shrines, oneto the north,   the other to thesouth.  First,  head south,     where ancient "
        "  ruins speak of  the Wind Fish...You will learn  much there...", // MSG_199 – Dialog0C7 – Owl
        "Hoot!  I see youhave read the   relief...  Whileit does say the island is but a dream of the    Wind Fish, no "
        "  one is really   sure...  Just asyou cannot know if a chest holdstreasure until  you open it, so you cannot "
        "tell if this is a    dream until you awaken...  The  only one who    knows for sure  is the Wind     Fish...  "
        "Trust  your feelings...Someday you willknow for sure...", // MSG_200 – Dialog0C8 – Owl
        "Hoot!  The many monsters of thisisland fear thatthe Wind Fish isabout to awaken!The monsters'   power is "
        "real!  They may conquerthe island and  destroy their   foes!  That day may come soon!  Now, go to the  "
        "mountain tower! Fly like a bird!Hoot! Hoot!", // MSG_201 – Dialog0C9 – Owl
        "Hoot hoot!      Your path is    not easy, but   you are almost  there. Go east. The Wind Fish   is getting    "
        "   restless.", // MSG_202 – Dialog0CA – Owl
        "Hoot!  It has   been some time  since our paths crossed, lad.   You must dive   into the waters of Martha's "
        "Bay to enter the    Catfish's Maw...The closer you  get to the Wind Fish, the more  restless he     sleeps.  "
        "Carry  onward!  Hoot!", // MSG_203 – Dialog0CB – Owl
        "Hoot!  That girlsang her song infront of the    Egg! Her 'Balladof the Wind     Fish' is a song of awakening! "
        "  Did she actuallyintend to wake  the Wind Fish?! The next Sirens'Instrument is inthe west.  Play your "
        "melodies sothe unliving    stones might    hear!  Show yourcourage!  The   Wind Fish waits for you!  Hoot!", // MSG_204 – Dialog0CC – Owl
        "The time has    come... The WindFish awaits...  Enter the Egg...Hoot! Hoot!", // MSG_205 – Dialog0CD – Owl
        "Hoot! Young lad,I mean... #####,the hero!  You  have defeated   the Nightmares! You have proven your wisdom,  "
        "  courage and     power!          ... ... ... ... As part of the  Wind Fish's     spirit, I am theguardian of "
        "his dream world...  But one day, theNightmares      entered the     dream and began wreaking havoc. Then you, "
        "#####,came to rescue  the island...   I have always   trusted in your courage to turn back the Night- mares.  "
        "Thank   you, #####... Mywork is done... The Wind Fish   will wake soon. Good bye...Hoot!", // MSG_206 –
                                                                                                    // Dialog0CE – Owl
        "Hoot! Young lad,I mean... #####,the hero!  You  have defeated   the Nightmares! You have proven your wisdom,  "
        "  courage and     power!          ... ... ... ... As part of the  Wind Fish's     spirit, I am theguardian of "
        "his dream world...  But one day, theNightmares      entered the     dream and began wreaking havoc. Then you, "
        "#####,came to rescue  the island...   I have always   trusted in your courage to turn back the Night- mares.  "
        "Thank   you, #####... Mywork is done... The Wind Fish   will wake soon. Good bye...Hoot!", // MSG_207 –
                                                                                                    // Dialog0CF – Owl
        "... ... ... ...  ... ... ... ... I AM THE WIND        FISH...    LONG HAS BEEN    MY SLUMBER...  IN MY "
        "DREAMS... AN EGG APPEARED     AND WAS    SURROUNDED BY AN  ISLAND, WITH  PEOPLE, ANIMALS,AN ENTIRE WORLD!... "
        "... ... ...   BUT, VERILY,  IT BE THE NATURE  OF DREAMS TO  END! WHEN I DOSTAWAKEN, KOHOLINT WILL BE "
        "GONE...ONLY THE MEMORY  OF THIS DREAM  LAND WILL EXIST   IN THE WAKING       WORLD...   SOMEDAY, THOU  MAY "
        "RECALL THIS  ISLAND...  THAT MEMORY MUST BE  THE REAL DREAM      WORLD...   ... ... ... ...  COME, #####... "
        "LET US AWAKEN...   TOGETHER!!",                                  // MSG_208 – Dialog0D0 – Wind Fish
        " PLAY THE EIGHT   INSTRUMENTS!  PLAY THE SONG OF   AWAKENING!!", // MSG_209 – Dialog0D1 – Wind Fish
        " PLAY THE EIGHT   INSTRUMENTS!  PLAY THE SONG OF   AWAKENING!!", // MSG_210 – Dialog0D2 – Wind Fish
        "Mermaid Statue  ",                                               // MSG_211 – Dialog0D3 – Map, probably
        "Mermaid Statue  ",                                               // MSG_212 – Dialog0D4 – Map, probably
        "Mermaid Statue  ",                                               // MSG_213 – Dialog0D5 – Map, probably
        "...#####, you   have beaten all the Nightmares! Climb the stairsbefore you!", // MSG_214 – Dialog0D6 – Owl
        "...#####, you   have beaten all the Nightmares! Climb the stairsbefore you!", // MSG_215 – Dialog0D7 – Owl
        "Ach! Vat are youlooking at vith zat magnifying  lens?  Stop it  at vonce!", // MSG_216 – Dialog0D8 – Schule
                                                                                     // Donavitch
        "  Hoot!  Hoot!  So you are the  lad who owns thesword...  Now I understand why  the monsters arestarting to "
        "act so violently... A courageous ladhas come to wakethe Wind Fish...It is said that you cannot leavethe "
        "island      unless you wake the Wind Fish...You should now  go north, to theMysterious      Forest.  I will "
        "wait for you    there!  Hoot!",               // MSG_217 – Dialog0D9 – Owl
        "Annoyance!  You are only gettingin the way!", // MSG_218 – Dialog0DA – Lanmola
        "Ribbit!  Ribbit!Hey, man, I'm   Mamu, on vocals!Brother, you    look like you   don't know      squat about   "
        "  music!  Ribbit!", // MSG_219 – Dialog0DB – Mamu
        "Ribbit!  Ribbit!I'm Mamu, on    vocals!  But I  don't need to   tell you that,  do I?  Everybodyknows me!  "
        "Want to hang out and listen to us    jam?  For 300   Rupees, we'll   let you listen  to a previously "
        "unreleased cut! What do you do?     Pay  Leave<ask>",   // MSG_220 – Dialog0DC – Mamu
        "Thank you...    Thank you very  much... Croak!",        // MSG_221 – Dialog0DD – Mamu
        "Well, that's a  shame, but we   don't play for  free!", // MSG_222 – Dialog0DE – Mamu
        "You've learned  The Frog's Song of Soul!  It's avery moving     tune... It can  even liven up   unliving "
        "things!",                                                                     // MSG_223 – Dialog0DF – Narrator
        "If you play thissong, you'll    make everything around you feel more alive!", // MSG_224 – Dialog0E0 – Mamu
        "Hey, Kid!  You  woke me up from a fine nap!!    ...Thanks a lot!But now, I'll   get my revenge! Are you "
        "ready?!     Yes  N-No<ask>", // MSG_225 – Dialog0E1 – Li'l Devil
        "I'll let you    carry more MagicPowder!  He He! Are you ready?!     Yes  N-No<ask>", // MSG_226 – Dialog0E2 –
                                                                                              // Li'l Devil
        "Okay, I'll let  you carry more  Bombs! He He He!Are you ready?!     Yes  N-No<ask>", // MSG_227 – Dialog0E3 –
                                                                                              // Li'l Devil
        "Fine, I'll let  you have more   arrows! Heh Heh!Are you ready?!     Yes  N-No<ask>", // MSG_228 – Dialog0E4 –
                                                                                              // Li'l Devil
        "Heh Heh Heh!    You deserve it! Now look at all that junk you   have to carry!  Hah!  Take care!See you "
        "again!", // MSG_229 – Dialog0E5 – Li'l Devil
        "??  There is a  picture carved  on the wall, butyou can't see itbecause it's toodark in here...", // MSG_230 –
                                                                                                           // Dialog0E6
                                                                                                           // – Narrator
        "TO THE FINDER...  THE ISLE OF   KOHOLINT, IS BUT  AN ILLUSION... HUMAN, MONSTER, SEA, SKY... A  SCENE ON THE "
        "LID OF A SLEEPER'S   EYE...  AWAKE THE DREAMER, AND  KOHOLINT WILL VANISH MUCH LIKE  A BUBBLE ON A NEEDLE... "
        "CAST- AWAY, YOU SHOULDKNOW THE TRUTH! ... ... ... ... What?  Illusion?", // MSG_231 – Dialog0E7 – Southern Face
                                                                                  // Shrine mural
        "You've found a  Gold Leaf! PressSTART to see    how many you've collected!", // MSG_232 – Dialog0E8 – Narrator
        "At last!  You'vegot the final   Golden Leaf!    Now go and see  Richard about   that key...", // MSG_233 –
                                                                                                       // Dialog0E9 –
                                                                                                       // Narrator
        "You've got a    Guardian Acorn! It will reduce  the damage you  take by half!", // MSG_234 – Dialog0EA –
                                                                                         // Narrator
        "You've got a    Guardian Acorn! It will reduce  the damage you  take by half!", // MSG_235 – Dialog0EB –
                                                                                         // Narrator
        "You've got a    Guardian Acorn! It will reduce  the damage you  take by half!", // MSG_236 – Dialog0EC –
                                                                                         // Narrator
        "You've got the  Mirror Shield!  You can now turnback the beams  you couldn't    block before!", // MSG_237 –
                                                                                                         // Dialog0ED –
                                                                                                         // Narrator
        "You've got a    more Powerful   Bracelet!  Now  you can almost  lift a whale!", // MSG_238 – Dialog0EE –
                                                                                         // Narrator
        "You found a     Secret Seashell!If you collect alot of these,   something good  is bound to     happen!", // MSG_239
                                                                                                                   // –
                                                                                                                   // Dialog0EF
                                                                                                                   // –
                                                                                                                   // Narrator
        "Want to go on a raft ride for a hundred Rupees?     Yes  No Way<ask>", // MSG_240 – Dialog0F0 – Raft Guy
        "Okay, the raft  is ready for yououtside!  Enjoy!",                     // MSG_241 – Dialog0F1 – Raft Guy
        "Waterfall at the    Shrine",      // MSG_242 – Dialog0F2 – Signpost, probably
        " South of the       Shrine",      // MSG_243 – Dialog0F3 – Signpost, probably
        "Entrance to the  Animal Village", // MSG_244 – Dialog0F4 – Signpost, probably
        "We were born of nightmares... Totake over this  world, we made  the Wind Fish   sleep endlessly!If the Wind "
        "Fishdoesn't wake up,this island willnever disappear!We would have   been the mastersof this place...But you "
        "had to  come here and   disrupt our     plans!  Heh heh!You can never   defeat us!!!    Let's rumble!", // MSG_245
                                                                                                                 // –
                                                                                                                 // Dialog0F5
                                                                                                                 // –
                                                                                                                 // Nightmare
                                                                                                                 // (final
                                                                                                                 // boss)
        "This island is  going to dis-   appear...  Our  world is going  to disappear... Our world...    Our... "
        "world... ", // MSG_246 – Dialog0F6 – Nightmare (final boss)
        "Wow!  #####, canI try this?!    What do you say?    Okay No Way<ask>", // MSG_247 – Dialog0F7 – Marin
        "C'mon!  I want  to do it! Can I?It looks so fun!    Yes  Okay<ask>",   // MSG_248 – Dialog0F8 – Marin
        "You're good!    You're a pro,   aren't you?     ... ... ... ... Well, beat it!  Pros aren't     allowed in "
        "here!",                                                  // MSG_249 – Dialog0F9 – Trendy Gamester
        "Go away!",                                               // MSG_250 – Dialog0FA – Hippo
        "Quit it!",                                               // MSG_251 – Dialog0FB – idk
        "This is not a   chest...  What? You knew that?  Okay.",  // MSG_252 – Dialog0FC – Narrator
        "##### checked   the chest.  Wow!This is a nice  chest!", // MSG_253 – Dialog0FD – Narrator
        "It's all ready, it is!  Take    care, as there'snot much there! Why not try a   bit in my hut?", // MSG_254 –
                                                                                                          // Dialog0FE –
                                                                                                          // Witch
        "Hey!  What are  ya doin' in my  chest?!  Where'dyou learn ta do such a thing?!", // MSG_255 – Dialog0FF – Tarin
        "You've got the  Full Moon Cello!",                                        // MSG_256 – Dialog100 – Narrator
        "You've got the  Conch Horn!",                                             // MSG_257 – Dialog101 – Narrator
        "You've got the  Sea Lily's Bell!",                                        // MSG_258 – Dialog102 – Narrator
        "You've got the  Surf Harp!",                                              // MSG_259 – Dialog103 – Narrator
        "You've got the  Wind Marimba!",                                           // MSG_260 – Dialog104 – Narrator
        "You've got the  Coral Triangle!",                                         // MSG_261 – Dialog105 – Narrator
        "You've got the  Organ of          Evening Calm!",                         // MSG_262 – Dialog106 – Narrator
        "You've got the  Thunder Drum!",                                           // MSG_263 – Dialog107 – Narrator
        "Hi! It's me, thephotographer!   You seem curiousabout Grandpa   Ulrira.", // MSG_264 – Dialog108 – Photographer
        "I'll call this  '##### Dis-     covers Ulrira's Secret!'",                // MSG_265 – Dialog109 – Photographer
        "#####, now run  away before he  finds you.",    // MSG_266 – Dialog10A – Photographer, probably
        "I'll go develop this. Come see  it later, OK?", // MSG_267 – Dialog10B – Photographer
        "I just LOVE to  take pictures.  Will you let me take your       picture?            YES  NO<ask>", // MSG_268 –
                                                                                                            // Dialog10C
                                                                                                            // –
                                                                                                            // Photographer
        "Go to the back  of the room and stand in front  of the screen.", // MSG_269 – Dialog10D – Photographer
        "Hey! I haven't  taken your      picture yet! Go back and stand  in front of the screen!", // MSG_270 – Dialog10E
                                                                                                   // – Photographer
        "I'll call this  'Here Stands A  Brave Man.'     Say cheese!", // MSG_271 – Dialog10F – Photographer
        "This owl statue is trying to saysomething, but  you can't       understand it   because it has  no beak.", // MSG_272 – Dialog110 – Narrator
        "'I've got what  was inside this box.  Come and  get it, if you  can!'  Master <skull>", // MSG_273 – Dialog111
                                                                                                 // – Master Stalfos (D5
                                                                                                 // Mini-Boss)
        "Gulp!  You foundme!  You're a   real pesky kid, you know that?!", // MSG_274 – Dialog112 – Master Stalfos (D5
                                                                           // Mini-Boss)
        "Arrgh!  I can't beat you!  I'm  outta here!", // MSG_275 – Dialog113 – Master Stalfos (D5 Mini-Boss)
        "You again?!  Youkeep going and  going... I can'toutlast you!    All right, let'sdo it!", // MSG_276 – Dialog114
                                                                                                  // – Master Stalfos
                                                                                                  // (D5 Mini-Boss)
        "WOOF! Dig! RUFF!",                                        // MSG_277 – Dialog115 – BowWow
        "You put the     missing scale inthe mermaid     statue!", // MSG_278 – Dialog116 – Narrator
        "Hey! Be more    careful next    time!",                   // MSG_279 – Dialog117 – idk
        "Hey, man!  When you want to savejust push all   the Buttons at  once!  Uhh...   Don't ask me    what that "
        "means,I'm just a kid!", // MSG_280 – Dialog118 – Kid
        "Well, it seems  that after you  save, you will  start at the    last door you   went through... I'm not "
        "really  sure why that is'cause I'm just a kid!", // MSG_281 – Dialog119 – Kid
        "I heard that youcan press SELECTto look at the  island map...   But, I don't    understand what they mean by  "
        "  that...", // MSG_282 – Dialog11A – Kid
        "When you're     running out of  Hearts, you'd   better enter a  house or cave...Why?  I have no idea, I'm "
        "just akid!",                                                                      // MSG_283 – Dialog11B – Kid
        "Hey, dude! What do you think of Marin?  Uhh...  I don't know,   I'm just a kid!", // MSG_284 – Dialog11C – Kid
        "Where are you   from, brother?  ...Outside the  island?  What is'outside?'  I'venever thought   about it...", // MSG_285 – Dialog11D – Kid
        "The giant egg ontop of TamaranchMountain?  They say the Wind    Fish is sleepinginside of it... Why?  I don't "
        "  know either...", // MSG_286 – Dialog11E – Kid
        "Dude!  You're   asking me when  we started to   live on this    island?  What doyou mean by     'when?'  "
        "Whoa!  The concept justmakes my head   hurt!", // MSG_287 – Dialog11F – Kid
        "Marin? She likesto go stare at  the ocean all byherself...  Why?Hey, I'm just a kid, don't ask  me!", // MSG_288
                                                                                                               // –
                                                                                                               // Dialog120
                                                                                                               // – Kid
        "Hey... Where're you two going   together?  Hunh?Uh, I didn't    mean anything...I'm just a kid!", // MSG_289 –
                                                                                                           // Dialog121
                                                                                                           // – Kid
        "Hey hey, bro!   About the Dream Shrine there... They say there'ssomething good  inside... ...   I better not "
        "sayanything else   as I'm just a   kid!",              // MSG_290 – Dialog122 – Kid
        "Hunh?!  Marin's not with you?   What happened toher?", // MSG_291 – Dialog123 – Kid, probably
        "WHOA! That's a  big one! Hey,   photo guy! Can  you take a      picture of this?", // MSG_292 – Dialog124 –
                                                                                            // Fisherman
        "I have a        feelin' that    I'll catch a bigfish again.", // MSG_293 – Dialog125 – Fisherman
        "If you keep me asecret, I'll    tell you some-  thing useful.   Go to Toronbo   Shores, use the magnifying "
        "glassand you will    find someone    like me.", // MSG_294 – Dialog126 – Zora
        "Tsk tsk...  Whata shame...",                    // MSG_295 – Dialog127 – Mamasha
        "Oh thank you!   You are indeed agenerous person!Ah!  I will giveyou this in     return!", // MSG_296 –
                                                                                                   // Dialog128 –
                                                                                                   // Mamasha, probably
        "You traded your <yoshi> for <ribbon>!  Maybe you can trade   the ribbon for  something else!", // MSG_297 –
                                                                                                        // Dialog129 –
                                                                                                        // Narrator
        "Because they alllook alike, evenI am sometimes  confused. . .   By the way, my  baby wants a    Yoshi Doll.   "
        "  I saw one at theTrendy Game,    but I couldn't  get it.",        // MSG_298 – Dialog12A – Mamasha
        "Oh!  Will you   give that doll  to my baby?!        Yes  No<ask>", // MSG_299 – Dialog12B – Mamasha
        "Because they alllook alike, evenI am sometimes  confused...     ", // MSG_300 – Dialog12C – Mamasha
        "Ahem!  Really, Imust insist thatyou not bring   that awful beastin here!  Leave that creature   outside and "
        "thenwe can talk!    Good Bye!", // MSG_301 – Dialog12D – Richard
        "You want to knowabout that      ghost? I'll bet he's happy      thanks to you.  Are you ready   for a "
        "picture?", // MSG_302 – Dialog12E – Photographer
        "Ho ho ho!       I really appre- ciate what you  did for my poor,precious BowWow!You are such a  nice boy!  "
        "How  can I ever repayyou?  I know...   SMOOOOOOOCH!  You got a rewardfrom Madam Meow-Meow... ... ... "
        "L-l-lucky!",                                                     // MSG_303 – Dialog12F – Madam MeowMeow
        "Ho ho ho!  My   BowWow is so    proud of his    fine fur coat!", // MSG_304 – Dialog130 – Madam MeowMeow
        "AIEEEEEEEE!     It's terrrrible!My BowWow was   dognapped by... Mo-mo-MOBLINS!! OHHH!  AHHHH!   Please! "
        "Somebodyhelp my poor    BowWow!!", // MSG_305 – Dialog131 – Madam MeowMeow
        "Oh thank you!   I'm so happy youbrought my baby back! Now, wouldyou be a dear   and take him fora walk? It "
        "wouldreally help me  out a lot!  You will?!  Thanks!", // MSG_306 – Dialog132 – Madam MeowMeow
        "Well... I prettymuch stick to   myself, me and  my letters...   My name's Write!The only thing Idon't like "
        "aboutmy hobby is thatI never receive a response...", // MSG_307 – Dialog133 – Weird Mr. Write
        "What's this?!  Aletter for me?! I'm so happy!   ...And look! Theletter came witha photograph!", // MSG_308 –
                                                                                                         // Dialog134 –
                                                                                                         // Weird Mr.
                                                                                                         // Write
        "Mmm... She's so beautiful...    I must give you something for   your trouble... Hmm...  Well, itlooks like "
        "all Ihave is this    broom... how'll that be?            Fine No...<ask>", // MSG_309 – Dialog135 – Weird Mr.
                                                                                    // Write
        "You got a Broom as your reward  from Mr. Write! But that photo  was not of...", // MSG_310 – Dialog136 –
                                                                                         // Narrator
        "Please! I reallymust insist you have this <broom>!        Okay No Way<ask>", // MSG_311 – Dialog137 – Weird Mr.
                                                                                      // Write
        "Oh boy!  Letter writing is such a great hobby!", // MSG_312 – Dialog138 – Weird Mr. Write
        "Hello!  I'm     writing back to Christine now!", // MSG_313 – Dialog139 – Weird Mr. Write
        "Salutations!    You wouldn't    know by the lookof me, but I    used to live in the castle! My  servants went "
        "  berserk and I   was forced to   flee to my      villa... So, youwant the key to Ukuku Prairie,  do you?  I "
        "may  be able to help you...  Let's   make... a deal, shall we? I wantyou to retrieve the Golden Leaf I left "
        "behind inthe castle when I fled...           Okay No Way<ask>", // MSG_314 – Dialog13A – Richard
        "I am impressed. There are five  leaves in all.  Remember to buy a shovel on yourway back.", // MSG_315 –
                                                                                                     // Dialog13B –
                                                                                                     // Richard
        "Well, I never!  I thought you   looked cowardly,but...  Please, leave me... justget out here!", // MSG_316 –
                                                                                                         // Dialog13C –
                                                                                                         // Richard
        "Ahh!  Tres Bien!I see you have  recovered all ofthe leaves! Now,move this box   and you will    find your     "
        "  reward!",                                                    // MSG_317 – Dialog13D – Richard
        "I am forever in your debt for   getting my      leaves back!", // MSG_318 – Dialog13E – Richard
        "Ah!  Bonjour!   #####, for the  love of justice,and my own sake,you must find   all the leaves!", // MSG_319 –
                                                                                                           // Dialog13F
                                                                                                           // – Richard
        "Er...Uh...Hmm...How to say...   Please call...  Outside...  ... It seems that   old man Ulrira  is a shy guy, "
        "  in person...", // MSG_320 – Dialog140 – Ulrira, Narrator
        "'BRRING! BRRING!Hello!  It's me,Ulrira!  Ask me anything about  the island!  If you get lost,   give me a "
        "call! Bye! CLICK!'", // MSG_321 – Dialog141 – Ulrira
        "'BRRING! BRRING!Hello, this is  Ulrira! ...Well,most Moblins    live in the Mys-terious Forest, but some live "
        "inthe caves of TalTal Heights...  I hope that is  what you wanted to know! CLICK!'", // MSG_322 – Dialog142 –
                                                                                              // Ulrira
        "'BRRING! BRRING!Yes, this is    Ulrira.  The    Indigestible    Flowers of      Goponga Swamp...Those flowers "
        "  are BowWow's    favorite.  Why  don't you take  him for a walk  there?  CLICK!'", // MSG_323 – Dialog143 –
                                                                                             // Ulrira
        "'BRRING! BRRING!Hi, it's Ulrira!...Have you met everyone on the island?  There'sa man named     Richard who   "
        "  lives in PotholeField, southeastof the village. Why not pay him a visit?  That'sall I can tell  you for "
        "now!    Bye!  CLICK!'", // MSG_324 – Dialog144 – Ulrira
        "'BRRING! BRRING!Old man Ulrira  here! ...Do you like bananas?   Try talking to  people in the   village "
        "again!  Bye!  CLICK!'", // MSG_325 – Dialog145 – Ulrira
        "'BRRING! BRRING!Ulrira speaking!You know, there is a library in the village thatmight have some good "
        "informationfor you!  Talk  to you later!   CLICK!'", // MSG_326 – Dialog146 – Ulrira
        "'BRRING! BRRING!Ya, it's Ulrira!You say you     haven't found   all five Golden Leaves? Go ask  the crow at "
        "the castle. I'm surehe can help you.Bye!            CLICK!'", // MSG_327 – Dialog147 – Ulrira
        "'BRRING! BRRING!Ulrira here! ...Shovel...  Did  you purchase a  shovel?  You mayfind something  if you dig "
        "here and there!  Bye!CLICK!'", // MSG_328 – Dialog148 – Ulrira
        "'BRRING! BRRING!Ya, it's Ulrira!The cave in the Ukuku Prairie isthe key!  Yes, Imean the key    cave, no pun  "
        "  intended!  Bye! CLICK!'", // MSG_329 – Dialog149 – Ulrira
        "'BRRING! BRRING!Hi, this is     Ulrira!  In the Yarna Desert,   which is locatedin the southeastof the "
        "island,  you will find   something calledthe Angler Key. Hmmm... How muchmore obvious do I have to be?   Bye! "
        "CLICK!'", // MSG_330 – Dialog14A – Ulrira
        "'BRRING! BRRING!This is Ulrira! Now you're beinghaunted by a    ghost?! Well,   how about takinghim where he  "
        "  wants to go?    Bye! CLICK!'", // MSG_331 – Dialog14B – Ulrira
        "'BRRING! BRRING!Hi, it's Ulrira!The Catfish's   mouth is wide   open?  It soundslike a great    place to "
        "dive!  Bye!  CLICK!'", // MSG_332 – Dialog14C – Ulrira
        "'BRRING! BRRING!Ulrira here! ...Have you been tothe Face Shrine?It is north of  Animal Village. That is a "
        "very  interesting     ruin... CLICK!'", // MSG_333 – Dialog14D – Ulrira
        "'BRRING! BRRING!Hi, it's Ulrira!Have you heard  of the Flying   Rooster of Mabe Village?  In thegood old "
        "days,  it used to give us rides if we  held it above   our heads... Nowit is lying     under the       "
        "Weathercock...  Is that useful  for you?  I hopeso! Bye! CLICK!'", // MSG_334 – Dialog14E – Ulrira
        "'BRRING! BRRING!Hi, it's Ulrira!The head of the turtle is in    your way?  Put  life into it andit will move! "
        "  It's true! True!Bye!  CLICK!'",                                 // MSG_335 – Dialog14F – Ulrira
        "   ...SWAMP...   A path opens...in the blooms...",                // MSG_336 – Dialog150 – Wind Fish, probably
        "  ...PRAIRIE...   ...PRAIRIE...  The Prairie is      waiting...", // MSG_337 – Dialog151 – Wind Fish, probably
        "...WATERFALL... It is hidden in the waterfall...",                // MSG_338 – Dialog152 – Wind Fish, probably
        "    ...BAY...   Your road goes  into the bay... ",                // MSG_339 – Dialog153 – Wind Fish, probably
        "   ...SHRINE... An island secretin the shrine...",                // MSG_340 – Dialog154 – Wind Fish, probably
        " ...MOUNTAIN... Something calls   ...from the     mountains...",  // MSG_341 – Dialog155 – Wind Fish, probably
        "  ...OCARINA... The music of theOcarina leads...",                // MSG_342 – Dialog156 – Wind Fish, probably
        "    ...EGG....  The Egg on the  mountain calls!",                 // MSG_343 – Dialog157 – Wind Fish, probably
        "Then YOU sweep  the island!",                                     // MSG_344 – Dialog158 – Grandma Yahoo
        "Then YOU sweep  the island!",                                     // MSG_345 – Dialog159 – Grandma Yahoo
        "YAHOO!   I'm    fine, and you?!",                                 // MSG_346 – Dialog15A – Grandma Yahoo
        "YAHOO!  I workedtoo hard and nowmy broom is wornto the handle!",  // MSG_347 – Dialog15B – Grandma Yahoo
        "YAHOO!  YAHOO!  A new broom?!   For me?  It is, isn't it?!          Yes  No<ask>", // MSG_348 – Dialog15C –
                                                                                            // Grandma Yahoo
        "Okay!  In returnyou can have    this fishing    hook I found    when I swept by the river bank!", // MSG_349 –
                                                                                                           // Dialog15D
                                                                                                           // – Grandma
                                                                                                           // Yahoo
        "You exchanged <broom> for the fishing hook <fishhook>!  What   will the fishinghook become?", // MSG_350 –
                                                                                                       // Dialog15E –
                                                                                                       // Narrator
        "YAHOO!  A new   broom!  Superb!",                                  // MSG_351 – Dialog15F – Grandma Yahoo
        "Kiiiki!  What?! All right, mutt!Let's battle!!",                   // MSG_352 – Dialog160 – Kiki
        "Chi-kiita! Chi- kiita!  Kiki themonkey!  Hungry!Kiki the monkey!", // MSG_353 – Dialog161 – Kiki
        "    <bananas>!    <bananas>!    Oooh! Ooh! Kiki!Monkeys!  Come! Repay him! Kiki!", // MSG_354 – Dialog162 – Kiki
        "Monkey business!Done!  Bye bye! Oooh!  Kiki!",                 // MSG_355 – Dialog163 – Kiki
        "You found a     stick a monkey  left behind...  You take it!", // MSG_356 – Dialog164 – Narrator
        "    <bananas>!    <bananas>!      Oooh!  Oooh!   Give to Kiki!?     Yes  No!<ask>", // MSG_357 – Dialog165 –
                                                                                             // Kiki, Narrator, Link
        "You don't know  the proper      etiquette when  dealing with a  lady, do you?   You should have brought "
        "flowers or something,   then I might be more inclined totalk with you...Oh yes, in my   case, hibiscus  are "
        "best...", // MSG_358 – Dialog166 – Christine
        "Oh, you brought me a hibiscus!  How sweet! Well,since you are   such a gentlemanI have a requestto make of "
        "you. Will you listen?    Yes  No<ask>", // MSG_359 – Dialog167 – Christine
        "I would like youto take this    letter to a Mr. Write who lives on the border ofthe Mysterious  Forest, "
        "please!",                                                       // MSG_360 – Dialog168 – Christine
        "...Is that so?  And I thought   you were a      gentleman...",  // MSG_361 – Dialog169 – Christine
        "You traded <flower2> fora goat's letter <letter>!  ...Great!?", // MSG_362 – Dialog16A – Narrator
        "You know, some- times I can't   help eating a   delicious piece of paper, even  if it's a letterto my darling "
        "  Mr. Write... Howembarrassing!",                           // MSG_363 – Dialog16B – Christine
        "You've saved    BowWow!  What a fearsome beast!",           // MSG_364 – Dialog16C – Narrator
        "Wow! The Roosterhas recovered!  He seems very   friendly!", // MSG_365 – Dialog16D – Narrator
        "'BRRING! BRRING!Ya, it's Ulrira!My wife went to the Animal      Village and leftme all alone.   Can you tell  "
        "  her to come homeas soon as she  is done         cleaning?       Bye!            CLICK!'", // MSG_366 –
                                                                                                     // Dialog16E –
                                                                                                     // Ulrira
        "Grandma's not   here. She's in  the Animal      Village. That's what Grandpa    Ulrira said on  the phone!", // MSG_367 – Dialog16F – Kid, probably
        "Yep, Papahl got lost, just like he said!  Now, Iam so famished Ican't move!  Canyou give me somevittles?      "
        "      Yes  Nope<ask>",      // MSG_368 – Dialog170 – Papahl
        "You're one cold hombre...", // MSG_369 – Dialog171 – Papahl
        "This <pineapple> is so    delicious!  I'm going to eat the<pineapple> right now!     Bon Appetit!", // MSG_370
                                                                                                             // –
                                                                                                             // Dialog172
                                                                                                             // – Papahl
        "AH!  This isn't meant to be a   reward...  Here,take this <flower2>!    It's a hibiscus!", // MSG_371 –
                                                                                                    // Dialog173 – Papahl
        "You traded the <pineapple>for the <flower2>!", // MSG_372 – Dialog174 – Narrator
        "Delicious!  Yum!I'm filled with energy, now!", // MSG_373 – Dialog175 – Papahl
        "I've got to say,thanks again!",                // MSG_374 – Dialog176 – Papahl, probably
        "Yep, Papahl got lost, just like he said!  Now, Iam so famished Ican't move!  Canyou give me somevittles?      "
        "      Nope Can't<ask>", // MSG_375 – Dialog177 – Papahl
        "She's had an    awful tragedy   in the house    across the way! It's just awful,and all I can dois sweep!", // MSG_376 – Dialog178 – Grandma Yahoo
        "I am the spirit of the mansion. I have been     waiting for     someone to      overcome the    darkness. "
        "Find  all the secret  shells and go   through the     gate to receive the ultimate    sword!", // MSG_377 –
                                                                                                        // Dialog179 –
                                                                                                        // Spirit of the
                                                                                                        // Mansion
        "Hmmm. No        response. You   must not have   enough shells.", // MSG_378 – Dialog17A – Narrator
        "My job here     is finished.",                                   // MSG_379 – Dialog17B – Spirit of the Mansion
        "Hey you! Have   you been to the Camera Shop in  Tal Tal Heights?Iyoung people    like to go thereand take     "
        "   pictures of     themselves.     Seems kinda     funny to me.", // MSG_380 – Dialog17C – idk, might be unused?
        "Step right up   and get your    souvenir photo!",                 // MSG_381 – Dialog17D – Map, probably
        "Good job!       Use it on your  enemies and see what happens.   If you run out, go to the for-  est, pick "
        "some  mushrooms, and  I will make you more.", // MSG_382 – Dialog17E – Witch
        ". . . .! I can'tmove! But I am  still all right.Your little     sword won't     break this      bottle!", // MSG_383
                                                                                                                   // –
                                                                                                                   // Dialog17F
                                                                                                                   // –
                                                                                                                   // Genie
                                                                                                                   // (D2
                                                                                                                   // Nightmare)
        "Make-up! Jewels!Dresses!  I wantit all!  Sigh...And some new    accessories     would be nice...", // MSG_384 –
                                                                                                            // Dialog180
                                                                                                            // – CiaoCiao
        "Make-up! Jewels!Dresses!  I wantit all!  Sigh...And some new    accessories     would be nice...Oh! That "
        "Ribbon!I need it!  Willyou trade for mydog food?           Yes  No!<ask>", // MSG_385 – Dialog181 – CiaoCiao,
                                                                                    // Link
        "You exchanged <ribbon> for <dogfood>! It's fullof juicy beef!", // MSG_386 – Dialog182 – Narrator
        "Lucky!  Thanks! Well, here's    your <dogfood>!",               // MSG_387 – Dialog183 – CiaoCiao
        "Eh?!  I can't   believe it!  Youare the worst!!",               // MSG_388 – Dialog184 – CiaoCiao
        "I am Manbo,     child of the SunFish!  Have you got an Ocarina?     Yes  No<ask>", // MSG_389 – Dialog185 –
                                                                                            // Manbo
        "Very well...    Glub Blub Bloop!",                                         // MSG_390 – Dialog186 – Manbo
        "Ahaha!  Then I  can teach you mysong! Bloop!",                             // MSG_391 – Dialog187 – Manbo
        "You've learned  Manbo's Mambo!  When you get outof the water,   play it!", // MSG_392 – Dialog188 – Narrator
        "I am Manbo,     child of the SunFish!  When you play my Mambo,  you can warp to Manbo Pond!  Trythis tune in "
        "thedungeons, too!  Cha-cha-cha!",                 // MSG_393 – Dialog189 – Manbo
        "Aha... You don'thave an Ocarina,so...Glub glub!", // MSG_394 – Dialog18A – Manbo
        "Chickens these  days don't have the fighting    spirit they usedto!  In the old days, they couldfly, flap "
        "flap! But now, see?   Cluck cluck!", // MSG_395 – Dialog18B – Henhouse Keeper
        "Wow!  Amazing!  That rooster is actually flying!It's just like Isaid, eh?  Have you tried to    hold him over "
        "  your head? CluckCluck!",                                  // MSG_396 – Dialog18C – Henhouse Keeper
        "Wooo!  Finally! This flying     rooster is the  greatest!", // MSG_397 – Dialog18D – Henhouse Keeper
        " Here Sleeps The Flying Rooster",                           // MSG_398 – Dialog18E – Weathervane
        "Iz zat zee      Mermaid scale?  I can't use it  now. I have to  werk on zis     drawing. You    should go "
        "finishzee mermaid     statue for me.", // MSG_399 – Dialog18F – Schule Donavitch
        "Ennh?  Who's    this suspicious-looking runt?!  Okay boys, let'sget ridda him!", // MSG_400 – Dialog190 – Moblin
        "You must be an  assassin sent byMadam MeowMeow  to rescue the   mutt!  You came here to get me, but it is I "
        "who will get you!!", // MSG_401 – Dialog191 – Moblin Chief
        "Oh, #####.  I   often come to   this village to sing, too!  It  seems that just about everyone  loves my "
        "'Balladof the Wind     Fish!'  #####,  what is your    favorite song?", // MSG_402 – Dialog192 – Marin
        "Please, don't   ever forget thissong...or me...",                       // MSG_403 – Dialog193 – Marin
        "Thank you for   everything!     #####, you are  the kindest boy I know.  One dayI made a wish tothe Wind "
        "Fish...What was the    wish?  It was...No, it's secret!", // MSG_404 – Dialog194 – Marin
        "#####, some day you will leave  this island...  I just know it  in my heart...  ...Don't ever   forget me... "
        "If you do, I'll    never forgive   you!",                          // MSG_405 – Dialog195 – Marin
        "... ... ... ... It seems to be  totally absorbedin Marin's song!", // MSG_406 – Dialog196 – Mutt, narrator
        "They say the    'Ballad of the  Wind Fish' is a song of awaken- ing.  I wonder, if the Wind Fishwakes up, "
        "will  he make my wish come true?", // MSG_407 – Dialog197 – Marin
        "Eh?  You want meto go in there? No, I think I'llwait out here...Take care of    yourself, #####!", // MSG_408 –
                                                                                                            // Dialog198
                                                                                                            // – Marin
        "Ahhh!  Ahhh, youare a bad boy,  #####!",                           // MSG_409 – Dialog199 – Marin
        "Here's some     bonus treatment!Behold!  Your   Hearts are full!", // MSG_410 – Dialog19A – Crazy Tracy
        "Ya, I am Schule Donavitch!  Zee mermaid statue  by zee bay iz mymasterpiece! ...To tell you zee truth, zis "
        "werk iz not complete!Zee art, it'z...difficult for   you to grasp, izit not?", // MSG_411 – Dialog19B – Schule
                                                                                        // Donavitch
        "  THE MOURNING       MERMAID        By SCHULE   ? ...A scale is missing...", // MSG_412 – Dialog19C – Mermaid
                                                                                      // Statue, Narrator
        "Seashell Mansion",                       // MSG_413 – Dialog19D – Signpost and maybe ; Map
        "Entrance to       Yarna Desert <right>", // MSG_414 – Dialog19E – Signpost, probably
        "   Mysterious        Forest      (It's a little  bit mysterious)", // MSG_415 – Dialog19F – Signpost
        "   Mysterious        Forest      (It's a little  bit mysterious)", // MSG_416 – Dialog1A0 – Signpost
        "Do you want to  challenge the   river rapids on a raft?  Proceedto the office atonce, please!", // MSG_417 –
                                                                                                         // Dialog1A1 –
                                                                                                         // Signpost,
                                                                                                         // probably
        "East <right> Ukuku           Prairie  Farther East      Animal Village", // MSG_418 – Dialog1A2 – Signpost
        "Mt. Tamaranch   ",                                    // MSG_419 – Dialog1A3 – Signpost and maybe ; Map
        "<right> Tail Cave     <down> Toronbo Shores",         // MSG_420 – Dialog1A4 – Signpost
        "<right> Gopongo Swamp <down> Mysterious      Forest", // MSG_421 – Dialog1A5 – Signpost
        "Beware of floorswith cracks!  A heavy person    should not standon them!", // MSG_422 – Dialog1A6 – Signpost
        "Telephone Booth ",                                           // MSG_423 – Dialog1A7 – Signpost and maybe ; Map
        "     DANGER!        Keep out!   (Except BowWow)",            // MSG_424 – Dialog1A8 – Signpost
        "<down> GO THIS WAY",                                         // MSG_425 – Dialog1A9 – Signpost
        "<up> GO THIS WAY",                                           // MSG_426 – Dialog1AA – Signpost
        "<right> GO THIS WAY",                                        // MSG_427 – Dialog1AB – Signpost
        "<left> GO THIS WAY",                                         // MSG_428 – Dialog1AC – Signpost
        " TRY AGAIN FROM    THE START",                               // MSG_429 – Dialog1AD – Signpost
        "GREAT!  YOU DID IT!  YOUR REWARDIS <right> THIS WAY!",       // MSG_430 – Dialog1AE – Signpost
        "GONE ON TOUR             MAMU",                              // MSG_431 – Dialog1AF – Signpost
        "<right> Crazy Tracy   <down> Manbo's Pond",                  // MSG_432 – Dialog1B0 – Signpost
        "<right> Animal Village<down> Martha's Bay",                  // MSG_433 – Dialog1B1 – Signpost
        "<right> Welcome to the Animal Village!",                     // MSG_434 – Dialog1B2 – Signpost
        "<right> Cemetery      <down> Ukuku Prairie ",                // MSG_435 – Dialog1B3 – Signpost
        "You're close to Tal Tal Heights.The Camera Shop is nearby.", // MSG_436 – Dialog1B4 – Signpost
        "<right> Tamaranch Mt. <left> Goponga Swamp ",                // MSG_437 – Dialog1B5 – Signpost
        "MUSIC, THE FISH STIRS IN THE EGGYOU ARE THERE...",           // MSG_438 – Dialog1B6 – Owl Statue
        "THE WIND FISH INNAME ONLY, FOR  IT IS NEITHER.",             // MSG_439 – Dialog1B7 – Owl Statue
        "IN SOIL SLEEPS  SECRETS, BENEATHYOUR SOLES...",              // MSG_440 – Dialog1B8 – Owl Statue
        "IN SOIL SLEEPS  SECRETS, BENEATHYOUR SOLES...",              // MSG_441 – Dialog1B9 – Owl Statue
        "AROUND HERE,    SECRETS ARE NIGH",                           // MSG_442 – Dialog1BA – Owl Statue
        "SECRETS ARE LIKEWATER WHEN IT   COMES TO BRIDGES",           // MSG_443 – Dialog1BB – Owl Statue
        "NOW YOU NEED    LOOK FAR FOR    A SECRET...",                // MSG_444 – Dialog1BC – Owl Statue
        "THE WIND FISH   SLUMBERS LONG...THE HERO'S LIFE GONE...",    // MSG_445 – Dialog1BD – Owl Statue
        "SEA BEARS FOAM, SLEEP BEARS     DREAMS. BOTH ENDIN THE SAME WAY CRASSSH!", // MSG_446 – Dialog1BE – Owl Statue
        "Oh?!  #####, I  see ya have a   nice stick...   Can I borrow it for a second?       Can  Can't<ask>", // MSG_447
                                                                                                               // –
                                                                                                               // Dialog1BF
                                                                                                               // – Tarin
        "Oh?!  #####, I  see ya have a   nice stick...   Can I borrow it for a second?       Can  Can't<ask>", // MSG_448
                                                                                                               // –
                                                                                                               // Dialog1C0
                                                                                                               // – Tarin
        "<stick> became the    honeycomb <honeycomb>!    You're not sure how it happened,but take it!", // MSG_449 –
                                                                                                        // Dialog1C1 –
                                                                                                        // Narrator
        "Hmmm, #####, youare mean!",                                        // MSG_450 – Dialog1C2 – Marin, probably
        "Beware of Sea   Urchins!  Don't touch them with your bare hands!", // MSG_451 – Dialog1C3 – Signpost
        "I was hungry    somethin' fierceso I went and   got bananas at  the beach...    #####, if you   want some, "
        "you  should go and   get some!", // MSG_452 – Dialog1C4 – Tarin
        "I was hungry    somethin' fierceso I went and   got bananas at  the beach...    #####, if you   want some, "
        "you  should go and   get some!", // MSG_453 – Dialog1C5 – Tarin
        "Welcome to      Sale's House O' Bananas!  I'm   Sale, this is myhouse! Actually,my hobby is col-lecting rare "
        "andunusual canned  food. My brotheris an artist, soI guess strange hobbies run in  the family!", // MSG_454 –
                                                                                                          // Dialog1C6 –
                                                                                                          // Sale
        "What's that you have?!  It's    canned food! Forheaven's sake,  man, give that <dogfood>to ME!!  PLEASE!He's "
        "hysterical!What do you do?     Give Don't<ask>", // MSG_455 – Dialog1C7 – Sale
        "Oh thank you!   I'll take that!",                // MSG_456 – Dialog1C8 – Sale
        "I don't suppose it would do any good to beg?    Well, if you    change your     mind, tell me.", // MSG_457 –
                                                                                                          // Dialog1C9 –
                                                                                                          // Sale
        "  MUNCH MUNCH!! ... ... ... ... That was great! I know it's not a fair trade,   but here's some bananas! "
        "YUM...",                                                                     // MSG_458 – Dialog1CA – Sale
        "You gave him <dogfood>  and got bananas <bananas> in return!    Good deal!", // MSG_459 – Dialog1CB – Narrator
        "Thank you again!That was yummy!",                                            // MSG_460 – Dialog1CC – Sale
        "Hey friend! Haveyou ever ridden the rapids on a raft?  You can, near Tal Tal    Heights!  You   ought to try "
        "it!", // MSG_461 – Dialog1CD – Sale
        "Rik'm rak'm! I  ran out of      ingredients!  IfI had honey, I  could make this fit for a king!", // MSG_462 –
                                                                                                           // Dialog1CE
                                                                                                           // – Chef Bear
        "Hi ho! Hey you! Is that possiblya <honeycomb> you have?   I just ran out! Will you swap itfor a pineapple?    "
        "Yes  No<ask>", // MSG_463 – Dialog1CF – Chef Bear
        "You exchanged <honeycomb> for <pineapple>!  It's notas sweet, but itis delicious!   ", // MSG_464 – Dialog1D0 –
                                                                                                // Narrator
        "That's a crying shame, but I    realize those   are a rare      delicacy!", // MSG_465 – Dialog1D1 – Chef Bear,
                                                                                     // probably
        "Hi ho! Yeah, I  know, that tub  of goo is asleepright in the wayto Yarna Desert!Once he's asleephe won't "
        "budge  for a loooooonngtime.  But hey! Take Little     Marin and wake  him up with her song!  That slobwould "
        "wake up   with a jump if  he heard her    sing, for sure! Heh heh heh!", // MSG_466 – Dialog1D2 – Chef Bear
        "My ultimate planis to open a    branch in Mabe  Village!",               // MSG_467 – Dialog1D3 – Chef Bear
        "HI HO!  Little  Marin!  Welcome!... ... ... ... Oh, shucks!  Youare here too... Sorry...", // MSG_468 –
                                                                                                    // Dialog1D4 – Chef
                                                                                                    // Bear
        "Oh, #####, I'm  glad you found  this place.     Will you stay   and talk to me  for a while?        Yes! "
        "No...<ask>",                                     // MSG_469 – Dialog1D5 – Marin
        "Okay, I'll just watch the waves for a while...", // MSG_470 – Dialog1D6 – Marin
        "At the beach...  Marin  <marin>",                // MSG_471 – Dialog1D7 – Marin
        "I wonder where  these coconut   trees come from?...Tarin says   there is nothingbeyond the sea, but I believe "
        "  there must be   something over  there...  When Idiscovered you, #####, my heart skipped a beat! I thought, "
        "this person has come to give us a    message...", // MSG_472 – Dialog1D8 – Marin
        "... ... ... ... ... ... ... ... If I was a sea  gull, I would   fly as far as I could!  I would fly to far "
        "away places and sing for many people!...If I wish to the Wind Fish,  I wonder if my  dream will come true... "
        "... ...", // MSG_473 – Dialog1D9 – Marin
        "Hey!  Are you   listening?      #####, are you  listening to me?    Yeah No...<ask>", // MSG_474 – Dialog1DA –
                                                                                               // Marin, Link
        "I want to know  everything aboutyou...Err...Uhh,Ha ha ha ha!", // MSG_475 – Dialog1DB – Marin
        "Hunh? The walruswants me to go  to him?  It     doesn't matter, I will go with  you to him...", // MSG_476 –
                                                                                                         // Dialog1DC –
                                                                                                         // Marin
        "Unnnngh! Owwwww!... ... ... ... I've sure lost  my taste for    honey!",         // MSG_477 – Dialog1DD – Tarin
        "Humph! Your headis always in theclouds! Will youplease listen tome next time?!", // MSG_478 – Dialog1DE – Marin
        "Ha! That's all  you've got?!    Get ready for   THIS!",                          // MSG_479 – Dialog1DF – idk
        "ZZZ ZZZ ZZZ ZZZ  ... <marin> ... <marin> ...", // MSG_480 – Dialog1E0 – Walrus
        "Yes, it's that  lazy walrus!    Shall we give   him a little    surprise?           Yes  No...<ask>", // MSG_481
                                                                                                               // –
                                                                                                               // Dialog1E1
                                                                                                               // –
                                                                                                               // Marin,
                                                                                                               // Link
        "Aha ha ha!  Wow!He certainly    woke with a     start!",           // MSG_482 – Dialog1E2 – Marin
        "Hunh?  Oh, he's calling me...   It's the same asalways... Ha ha!", // MSG_483 – Dialog1E3 – Marin
        "You're right, itwould be mean towake him up now!Let's let him   sleep some more!", // MSG_484 – Dialog1E4 –
                                                                                            // Marin
        "#####, I'm goingto the Animal   Village!  Pleasedrop by, okay?", // MSG_485 – Dialog1E5 – Marin, probably
        "Arfh! Arfh! Arf! <marin>  <marin>!  <marin>   <marin>!  ..... <link>?? ", // MSG_486 – Dialog1E6 – idk
        "It's no use,    little buddy!  Afish took my    hook... I keep  casting my line into the water, but I haven't "
        "  got a bite... I thought this    would happen...", // MSG_487 – Dialog1E7 – Fisherman
        "Oh! What is thatyou have in yourhand?  It's not a fishing hook, is it?  You had better let me   have it.  "
        "I'll  give you my nextcatch if you letme have it...       Okay No<ask>", // MSG_488 – Dialog1E8 – Fisherman
        "Keep your eyes  open and watch  a pro at work.",                         // MSG_489 – Dialog1E9 – Fisherman
        "You should be   more kind to me!I thought we    were buddies!",          // MSG_490 – Dialog1EA – Fisherman
        "My, that's a    BIIIIG one!",                                            // MSG_491 – Dialog1EB – Fisherman
        "The <fishhook> became a  necklace <bra>!     L-l-lucky!",                // MSG_492 – Dialog1EC – Narrator
        "I can't wait to see what I'll   catch next!",                            // MSG_493 – Dialog1ED – Fisherman
        "My husband is   lost in the     woods! Please   go find him!",           // MSG_494 – Dialog1EE – Mamasha
        "Hey, you can seeme?! You must   have a magnify- ing glass. I'm  not a trouble   maker. I just   want to live "
        "in peace.", // MSG_495 – Dialog1EF – Secret Zora
        "When I was swim-ming in the bay,the waves took avery important  necklace from   around my neck! If you find "
        "it, I will let you  take a scale    from my tail!   ", // MSG_496 – Dialog1F0 – Mermaid
        "I have already  looked around   here!",                // MSG_497 – Dialog1F1 – Mermaid
        "Ahh!  That's it!That's my neck- lace!  Give it! Give it back!  Iwill give you a scale as I said!    Give "
        "Keep<ask>",                       // MSG_498 – Dialog1F2 – Mermaid
        "Promise!  You'llonly take one!",  // MSG_499 – Dialog1F3 – Mermaid
        "You are heart-  less and cruel!", // MSG_500 – Dialog1F4 – Mermaid
        "You returned thenecklace <bra> and  got a scale <scale> ofthe mermaid's   tail.  How will you use this?", // MSG_501
                                                                                                                   // –
                                                                                                                   // Dialog1F5
                                                                                                                   // –
                                                                                                                   // Narrator
        "I'll call this  'I Was Very     Afraid.' Smile!", // MSG_502 – Dialog1F6 – Photographer
        "An artist once  asked me to posefor him, and he wanted a scale, too...  Can the legend of the   Magnifying "
        "Lens be true...?", // MSG_503 – Dialog1F7 – Mermaid
        "Hi there! It's  me, the photo-  grapher! You sayZora is in the  house? I HAVE totake a picture  of that. I'll "
        "  call it 'I FoundZora.'",             // MSG_504 – Dialog1F8 – Photographer
        "Richard's Villa ",                     // MSG_505 – Dialog1F9 – Signpost maybe, and ; Map maybe
        "Kanalet Castle  10 Min. <right> <up>", // MSG_506 – Dialog1FA – Signpost
        "Kanalet Castle  5 Min. <right>",       // MSG_507 – Dialog1FB – Signpost
        "Kanalet Castle  50 Paces <up>",        // MSG_508 – Dialog1FC – Signpost
        "'BRRING! BRRING! BRRING! CLICK! Yeees!  It's theBucket Mouse!   Thanks for call-ing! ...Well... CLICK!'  ??? "
        "...You must have   dialed a wrong  number...", // MSG_509 – Dialog1FD – Bucket Mouse
        "Oh!  It's a big one!  And it hasa Piece of      Heart, too!  Youget a 20 Rupee  prize on top of that! Try "
        "again?    Yes  No<ask>", // MSG_510 – Dialog1FE – Fisherman, Link
        "Oh!  It's a big one!  And it hasa Piece of      Heart, too!  Youhave completed  another Heart   Container!  "
        "On  top of that, youget a 20 Rupee  prize! Want to  try again?          Yes  No<ask>", // MSG_511 – Dialog1FF –
                                                                                                // Fisherman, Link
        " 'How To Handle    Your Shield     Like A Pro!' Read this book?     YES  NO<ask>", // MSG_512 – Dialog200 –
                                                                                            // Book, Narrator
        "'If you hold theButton down, youcan defend your-self from enemy attacks, and youcan flip some   enemies, "
        "too... Besides the     standard shield there is also a mirrored varietywhich can defendagainst beams!'", // MSG_513
                                                                                                                  // –
                                                                                                                  // Dialog201
                                                                                                                  // –
                                                                                                                  // Book
        " 'Selecting The    Item That's    Right For You'Read this book?     YES  NO<ask>", // MSG_514 – Dialog202 –
                                                                                            // Book, Narrator
        "'You can select your favorite   item for the A  and B Buttons onthe Sub-Screen. Using different items, you "
        "can  fight without a sword!  Try manydifferent thingsto find what's  right for you!'", // MSG_515 – Dialog203 –
                                                                                                // Book
        " 'Auto Map and  Memo Guide Book'Read this book?     YES  NO<ask>", // MSG_516 – Dialog204 – Book, Narrator
        "'You can see an island map by   pressing the    SELECT Button.  The dark parts  of the map are  places you "
        "have not yet visited.Move the cursor and press the A Button to get   more informationabout an area,  or to "
        "replay themessage you got there...'  Ahhh!How convenient!",        // MSG_517 – Dialog205 – Book, Narrator
        " 'Secrets Of The Whirling Blade'Read this book?     YES  NO<ask>", // MSG_518 – Dialog206 – Book, Narrator
        "'The Whirling   Blade technique has been handed down from gener-ation to gener- ation by the    family of the "
        "  hero. To use it,hold down the   Sword Button andbuild up your   power.  When youhave enough, youcan release "
        "the Button!  Can youmaster this?'",                                // MSG_519 – Dialog207 – Book
        "'The Properties   Of Warp Holes'Read this book?     YES  NO<ask>", // MSG_520 – Dialog208 – Book, Narrator
        "'There are some Warp Holes on   Koholint Island.You can warp to and fro using   these holes.  Ifyou jump into "
        "  the Warp Hole   at which you    arrived, you    will go to the  next one in the sequence.  You  can only "
        "warp toa hole you have seen with your  own eyes...'", // MSG_521 – Dialog209 – Book
        "'Fun With Bombs'Read this book?     YES  NO<ask>",    // MSG_522 – Dialog20A – Book, Narrator
        "'After you put aBomb down, you  can pick it up  by pressing the Button again.   You can then    throw it by   "
        "  pushing the     Button one more time.  Did you  know that?'", // MSG_523 – Dialog20B – Book
        "   'Atlas Of    Koholint Island'You can move thecursor and look up the name of aplace...  Do youwant to look "
        "at this map?           Look Don't<ask>", // MSG_524 – Dialog20C – Book, Narrator
        " 'Dark Secrets    And Mysteries    Of Koholint' Do you really   want to read it?    YES  NO<ask>", // MSG_525 –
                                                                                                            // Dialog20D
                                                                                                            // – Book,
                                                                                                            // Narrator
        "Gasp! Wha-What'sthis! ... ...   You can't read  the tiny print  without the aid of a magnifying glass...", // MSG_526 – Dialog20E – Book, Narrator
        "...my grave...  ...take me...   ...my grave...",                   // MSG_527 – Dialog20F – Ghost
        "...my grave...  ...take me...   ...my grave...",                   // MSG_528 – Dialog210 – Ghost
        "...the house...  ...take me...  ...the house... ...at the bay...", // MSG_529 – Dialog211 – Ghost
        "...N-N-No!...   ...N-not there!",                                  // MSG_530 – Dialog212 – Ghost
        "   ...Here!...     ...enter...   ...my house...",                  // MSG_531 – Dialog213 – Ghost
        " ...Nostalgia... ...unchanged... ...boo hoo...",                   // MSG_532 – Dialog214 – Ghost
        "  ...Enough...   ...cemetery...   ...take me...  ...my grave...",  // MSG_533 – Dialog215 – Ghost
        "...Thank you...  ...a jar...    ...in my home......look inside.....bye...bye...", // MSG_534 – Dialog216 – Ghost
        "Round and round,the passageways of the Egg...   <left> <left> <up> <right> <right> <up> <left> <up> ??  "
        "...Hmmmmmm, this book reeks of secrets...", // MSG_535 – Dialog217 – Book, Narrator
        "Round and round,the passageways of the Egg...   <right> <up> <up> <right> <up> <up> <right> <up> ??  "
        "...Hmmmmmm, this book reeks of secrets...", // MSG_536 – Dialog218 – Book, Narrator
        "Round and round,the passageways of the Egg...   <left> <up> <right> <up> <left> <up> <right> <up> ??  "
        "...Hmmmmmm, this book reeks of secrets...", // MSG_537 – Dialog219 – Book, Narrator
        "Round and round,the passageways of the Egg...   <right> <right> <right> <right> <up> <up> <up> <up> ??  "
        "...Hmmmmmm, this book reeks of secrets...",                 // MSG_538 – Dialog21A – Book, Narrator
        "...You're late! I thought you'd never come back!",          // MSG_539 – Dialog21B – Marin
        "...EEEK!  You'rehurt!  Arrrgh!  Don't be so     reckless!", // MSG_540 – Dialog21C – Marin
        "#####! You're   back!  Are you  hurt?",                     // MSG_541 – Dialog21D – Marin
        "...You idiot!   I told you this would happen... Eh?!  What?  I  didn't say any- thing, really!", // MSG_542 –
                                                                                                          // Dialog21E –
                                                                                                          // Marin
        "Hey buddy!  It'sserious!  Yeah, really serious!!Yeah, it is!    The Moblins cameto the village! Yeah, that's  "
        "  right!  A whole gang of Moblins!Then... It's forreal!  They all went to the     house...  Yeah, that house, "
        "and then they did   something at BowWow's house!!   It was a really bad scene, with the M-m-moblins!So, I "
        "mean, ahh!... ... ... ... ... ... ... ... It might be     faster to find  out for yourselfwhat happened!", // MSG_543 – Dialog21F – Kid
        "Hey buddy!  It'sserious!  Yeah, really serious!!Yeah, it is!    The Moblins cameto the village! Yeah, that's  "
        "  right!  A whole gang of Moblins!Then... It's forreal!  They all went to the     house...  Yeah, that house, "
        "and then they did   something at BowWow's house!!   It was a really bad scene, with the M-m-moblins!So, I "
        "mean, ahh!... ... ... ... ... ... ... ... It might be     faster to find  out for yourselfwhat happened!", // MSG_544 – Dialog220 – Kid
        "I found a good  item washed up  on the beach... I'll trade it toyou for what youhave in your B  Button...     "
        "      Okay No<ask>", // MSG_545 – Dialog221 – Secret Goriya
        "Okay, let's do  it!  When you   don't want the  Boomerang any   more, come back!", // MSG_546 – Dialog222 –
                                                                                            // Secret Goriya
        "Oh, yeah, uh... okay, whatever.",                               // MSG_547 – Dialog223 – Secret Goriya
        "You got the     Boomerang in    exchange for theitem you had.", // MSG_548 – Dialog224 – Narrator
        "Give me back theBoomerang, I begyou! I'll returnthe item you    gave to me!         Okay Not Now<ask>", // MSG_549
                                                                                                                 // –
                                                                                                                 // Dialog225
                                                                                                                 // –
                                                                                                                 // Secret
                                                                                                                 // Goriya,
                                                                                                                 // Link
        "The item came   back to you. Youreturned the    Boomerang.",  // MSG_550 – Dialog226 – Narrator
        "Ah... Don't giveme that item... How about some- thing else?", // MSG_551 – Dialog227 – Secret Goriya
        "'BRRING! BRRING!Ya, it's Ulrira!You haven't     found the 5     Golden Leaves?  Keep an eye on  the ones you  "
        "  have. Someone   might try and   take 'em! Bye!  CLICK!'", // MSG_552 – Dialog228 – Ulrira
        "'BRRING! BRRING!Ya, it's Ulrira!You haven't     found the 5     Golden Leaves?  Try bombing sus-picious "
        "places. Hope that helps.Bye!            CLICK!'", // MSG_553 – Dialog229 – Ulrira
        "'BRRING! BRRING!Ya, it's Ulrira!You haven't     found the 5     Golden Leaves?  Go scare that   crow by the   "
        "  castle and see  if that helps!  Bye!            CLICK!'", // MSG_554 – Dialog22A – Ulrira
        "'The Travels of #####' Do you   want to look at your album?         Look Don't<ask>", // MSG_555 – Dialog22B –
                                                                                               // Photo Album, Narrator
        "Which picture   would you like  to see? Use <dpad> toselect, then    press the A     Button!", // MSG_556 –
                                                                                                        // Dialog22C –
                                                                                                        // Narrator
        "You are near theEagle's Tower.  Beware of the   bird!", // MSG_557 – Dialog22D – Signpost, probably
        "Hi, #####. You  know I love to  take pictures.  Wouldn't this   old castle make a great photo?", // MSG_558 –
                                                                                                          // Dialog22E –
                                                                                                          // Photographer
        "Hunh?  A keyholehere?  It says, 'Tale Keyhole'",   // MSG_559 – Dialog22F – Narrator
        "Hunh?  A keyholehere?  It says, 'Tale Keyhole'",   // MSG_560 – Dialog230 – Narrator
        "Hunh?  A keyholehere?  It says, 'Slime Keyhole'",  // MSG_561 – Dialog231 – Narrator
        "Hunh?  A keyholehere?  It says, 'Angler Keyhole'", // MSG_562 – Dialog232 – Narrator
        "Hunh?  A keyholehere?  It says, 'Bird Keyhole'",   // MSG_563 – Dialog233 – Narrator
        "Hunh?  A keyholehere?  It says, 'Face Keyhole'",   // MSG_564 – Dialog234 – Narrator
        "Somebody, HELP!",                                  // MSG_565 – Dialog235 – Marin
        "Hey!  #####!    Some monsters   put me up here! What should I   do?!  I'm afraidof heights!!", // MSG_566 –
                                                                                                        // Dialog236 –
                                                                                                        // Marin
        "Yow!  That was asurprise! #####,thank you!",                          // MSG_567 – Dialog237 – Marin
        "... ... ... ... ... ... ... ... Say... #####... ",                    // MSG_568 – Dialog238 – Marin
        "Uhh... I don't  know how to say this... but...",                      // MSG_569 – Dialog239 – Marin
        R"(Hunh?!  Tarin??!... ... ... ... Uh... Nevermind,I... I gotta go!)", // MSG_570 – Dialog23A – Marin
        "MAAAAAAARINNNN!!",                                                    // MSG_571 – Dialog23B – Tarin
        "Nothing yet?! I grow tired of   waiting. I want those Golden    Leaves deliveredsoon!           Courage like  "
        "  this deserves a photo, don't youthink?", // MSG_572 – Dialog23C – Richard
        "Hey, Marin and  #####! Are you  taking pictures?You should take pictures of     everyone,       including me.", // MSG_573 – Dialog23D – Tarin
        "I use this to   take pictures.  Are you ready?  Say 'mushroom!'", // MSG_574 – Dialog23E – Photographer,
                                                                           // probably
        "OK, I'm done.   I'll go home    now.", // MSG_575 – Dialog23F – Photographer, probably
        "'BRRING! BRRING!This is Ulrira! Oh, I heard fromgrandma that    there is some-  thing hidden    behind the "
        "fallsin the Tal Tal  Mountains.  Doesthat help?  Bye!CLICK!'", // MSG_576 – Dialog240 – Ulrira
        "'BRRING! BRRING!Ulrira here...  Yes, when I was just a lad, I   recall seeing a high tower in   the "
        "mountains!  You should go   there!  Is that helpful for you?Bye! CLICK!'", // MSG_577 – Dialog241 – Ulrira
        "'BRRING! BRRING!Hello, this is  Ulrira speaking!#####, it's timefor you to face the Egg on Mt.  Tamaranch!  "
        "Be  careful, #####! Bye!  CLICK!'", // MSG_578 – Dialog242 – Ulrira
        "'BRRING! BRRING!This is Ulrira! You're lost in  the Egg?  Hmmmm.No sir, I can't help you on thatone.  How "
        "about the library?    And hey, don't  stop calling me because I didn'tknow one little answer!  CLICK!'", // MSG_579
                                                                                                                  // –
                                                                                                                  // Dialog243
                                                                                                                  // –
                                                                                                                  // Ulrira
        "'BRRING! BRRING!Ulrira at your  service!  Oh?   You should take BowWow home now,Madam MeowMeow  would "
        "appreciateit! Bye! CLICK!'", // MSG_580 – Dialog244 – Ulrira
        "'BRRING! BRRING!Yeah, this is   Ulrira!  You arestarting to likemusic, eh?      Well, a frog    named Mamu, "
        "who lives in the    Signpost Maze,  might know some new songs, but  he charges a lotto play them!   Bye!  "
        "CLICK!'", // MSG_581 – Dialog245 – Ulrira
        "'BRRING! BRRING!Hi, it's Ulrira!You are doing   great!  Your    efforts will endsoon... By the  way, have you "
        "  visited the Hen House on the    mountain?  Thereis a cave nearbywith something  important in it.Bye!  "
        "CLICK!'", // MSG_582 – Dialog246 – Ulrira
        "'BRRING! BRRING!Ulrira speaking!Are your enemiestoo strong for  you?  In that   case, you bettercollect all "
        "the Seashells...Justbelieve in your-self and do yourbest!  CLICK!'", // MSG_583 – Dialog247 – Ulrira
        "'BRRING! BRRING!Ulrira here! ...Go for it!      You're almost   there! I'm pull-ing for you!    Bye!  CLICK!'", // MSG_584 – Dialog248 – Ulrira
        "Go ahead and    take a picture  of me. Any angleyou like!", // MSG_585 – Dialog249 – idk
        "Yarna Desert?   There's a way toget there to thesouth, but you  might not be    able to get     through if "
        "that lazy walrus is  in the way!",                                 // MSG_586 – Dialog24A – idk
        "Ahhh... Sigh... On such a nice  day, we need a  song from Marin!", // MSG_587 – Dialog24B – idk
        "Hey! Did ya knowAnimal Village  and Mabe Villageare sister      cities?  Yes,   even though theyaren't large  "
        "  enough to be    called cities...Anyway, I heard from a very goodsource that theyhave a Dream    Shrine in "
        "Mabe, and that it has something good  inside...  Is   that true?", // MSG_588 – Dialog24C – idk
        "I can't go to   Mabe Village    because of all  the monsters.   I hope Marin    is all right.", // MSG_589 –
                                                                                                         // Dialog24D –
                                                                                                         // idk
        "Have you heard  of the Flying   Rooster?  They  say it lived in Mabe Village a  long time ago...I wonder if "
        "it'strue...",                                                                      // MSG_590 – Dialog24E – idk
        "Aaaah, Little   Marin... I want her to come backagain...Her songis the best...",   // MSG_591 – Dialog24F – idk
        "I dreamed that  I turned into a carrot last     night...  What  an odd dream...",  // MSG_592 – Dialog250 – idk
        "Eh?  How can an animal talk?    How?  Hey, I'm  just a rabbit,  so I don't know!", // MSG_593 – Dialog251 –
                                                                                            // Rabbit
        "Ahhh!  It's her!Little Marin!!",                                                   // MSG_594 – Dialog252 – idk
        "If you have no  courage,then    you have no     strength.       Gravestones     won't move for  cowards.", // MSG_595 – Dialog253 – idk
        "I'm not afraid. I just decided  to wait at home.", // MSG_596 – Dialog254 – idk
        "This is my firstwalk with you,  #####.",           // MSG_597 – Dialog255 – Marin
        ". . . . .",                                        // MSG_598 – Dialog256 – Marin
        "This cliff will be our secret   place. ",          // MSG_599 – Dialog257 – Marin
        "Aren't you goingto say anything?",                 // MSG_600 – Dialog258 – Marin
        "Oh how I love   pictures! Why   don't you take  a picture when  no one is       around? You can call it . . .", // MSG_601 – Dialog259 – Photographer, maybe
        "You've got the  Blue Clothes!   Your damage willbe reduced by   half!", // MSG_602 – Dialog25A – Narrator
        "You've got the  Red Clothes!    Your body is    full of energy! ",      // MSG_603 – Dialog25B – Narrator
        "Red for offense,blue for        defense. Which  do you choose?      RED  BLUE<ask>", // MSG_604 – Dialog25C –
                                                                                              // Fairy Queen (Color
                                                                                              // Dungeon)
        "Are you sure?       YES  NO<ask>",     // MSG_605 – Dialog25D – Fairy Queen (Color Dungeon), Link
        "The fairy queen is waiting for  you.", // MSG_606 – Dialog25E – Dion (Color Dungeon)
        "Do you have the powder? If not, you must go     back.", // MSG_607 – Dialog25F – Gar (Color Dungeon)
        "Our colors are  never the same! If I am red, he is blue! If he  is red, I am    blue! What coloris my cloth?  "
        "      Red  Blue<ask>", // MSG_608 – Dialog260 – Color Guard (Color Dungeon)
        "BOO! I am no    weakling! Your  pitiful sword isno match for me!", // MSG_609 – Dialog261 – idk
        "I am sorry, but this is the     Color Dungeon.  Only those with the power of    color may enter.If you can "
        "tell who wears red   and who wears   blue, you may   enter.          Farewell.", // MSG_610 – Dialog262 – Color
                                                                                          // Guard (Color Dungeon)
        "Here is your    clue. Make      all the red     blue.", // MSG_611 – Dialog263 – idk (Color Dungeon)
        "No,  no. Take a closer look and try again.",            // MSG_612 – Dialog264 – idk
        "Don't tell      anyone.",                               // MSG_613 – Dialog265 – idk
        "Do you want to  read this book?     YES  NO<ask>",      // MSG_614 – Dialog266 – Narrator
        "New world of    color under the 5 gravestones.                     3<up>  4<right>  5<up>      2<left>  "
        "1<down>       Try with all    your might. Opena new path!     Whoever is      worthy receives the power of    "
        "color. I wonder what the world  of color is?", // MSG_615 – Dialog267 – Book, Narrator
        "Welcome, #####. I admire you forcoming this far.I will give you the power of    color. If you   want offense, "
        "  choose red. If  you want defensechoose blue.    Which power do  you want?           RED  BLUE<ask>", // MSG_616
                                                                                                                // –
                                                                                                                // Dialog268
                                                                                                                // –
                                                                                                                // Fairy
                                                                                                                // Queen
                                                                                                                // (Color
                                                                                                                // Dungeon)
        "You fool! Your  sword won't     work! Try       something else!", // MSG_617 – Dialog269 – idk
        "What a greedy   fool! You want  more power?! A  buffoon like youmight as well   give up and     go home!", // MSG_618 – Dialog26A – idk
        "Relax and close your eyes.",                                 // MSG_619 – Dialog26B – Great Fairy
        "I will now take you out.",                                   // MSG_620 – Dialog26C – idk (Color Dungeon)
        "Blue is safe.   Yellow is       caution. Red is danger.",    // MSG_621 – Dialog26D – idk (Color Dungeon)
        "Yellow is       caution. Red is danger,Take     your time.", // MSG_622 – Dialog26E – idk (Color Dungeon)
        "Blue. Start     over. Yellow is caution. Red is danger.",    // MSG_623 – Dialog26F – idk (Color Dungeon)
        "Hey, that looks great! I'll callit '##### Plays With BowWow!'   Now get closer  to BowWow!", // MSG_624 –
                                                                                                      // Dialog270 –
                                                                                                      // Photographer
        "Grrrr!",                                 // MSG_625 – Dialog271 – BowWow
        "#####, get      closer!",                // MSG_626 – Dialog272 – Photographer
        "Grrrr! Grrrr!!",                         // MSG_627 – Dialog273 – BowWow
        "Much closer! OK,I'm ready.      Smile!", // MSG_628 – Dialog274 – Photographer
        "Grrrr! Grrrr!!  GRRRR!",                 // MSG_629 – Dialog275 – BowWow
        "Ha ha ha! Do it!Do it!  Do it   moooore! ... ...Hunh?  No, it's nothing... I    didn't mean it.", // MSG_630 –
                                                                                                           // Dialog276
                                                                                                           // – Marin
        "Not very good...Eh?  What?  Did I say something?No, you're hear-ing things...", // MSG_631 – Dialog277 – Marin
        "#####, do you   always look in  other people's  drawers?",                      // MSG_632 – Dialog278 – Marin
        "Great!  Dig it! Dig it!  Dig to the center of   the earth!!",                   // MSG_633 – Dialog279 – Marin
        "Whew!  What a   surprise!",                                        // MSG_634 – Dialog27A – Marin, probably
        "Ohh!  I'm sorry!Are you okay?!  #####?",                           // MSG_635 – Dialog27B – Marin, probably
        "Hey Mon!",                                                         // MSG_636 – Dialog27C – Cukeman
        "You know me, I  like short namesthe best...",                      // MSG_637 – Dialog27D – Cukeman
        "It can display  millions of     polygons!",                        // MSG_638 – Dialog27E – Cukeman
        "I definitely    need it, as soonas possible!",                     // MSG_639 – Dialog27F – Cukeman
        "Turn aside the  spined ones witha shield...",                      // MSG_640 – Dialog280 – Owl Statue
        "First, defeat   the imprisoned  Pols Voice,     Last, Stalfos...", // MSG_641 – Dialog281 – Owl Statue
        "Far away...     Do not fear,    dash and fly!",                    // MSG_642 – Dialog282 – Owl Statue
        "The glint of thetile will be    your guide...",                    // MSG_643 – Dialog283 – Owl Statue
        "Dive under wheretorchlight beamsdo cross...",                      // MSG_644 – Dialog284 – Owl Statue
        "Enter the space where the eyes  have walls...",                    // MSG_645 – Dialog285 – Owl Statue
        "The riddle is   solved when the pillars fall!",                    // MSG_646 – Dialog286 – Owl Statue
        "Fill all the    holes with the  rock that rolls,this (<dpad>) is the key!", // MSG_647 – Dialog287 – Owl Statue
        "If there is a   door that you   can't open, movea stone block.",            // MSG_648 – Dialog288 – Owl Statue
        "Make every blockdesign the same.A new path will open.",                     // MSG_649 – Dialog289 – Owl Statue
        "Part of the     floor is raised.Tap the blue    crystal.",                  // MSG_650 – Dialog28A – Owl Statue
        "To defeat the   black monster   with the hard   shell, feed him something ex-   plosive.", // MSG_651 –
                                                                                                    // Dialog28B – Owl
                                                                                                    // Statue
        "Poke suspicious parts of the    wall with your  sword and listento the sounds itmakes.", // MSG_652 – Dialog28C
                                                                                                  // – Owl Statue
        "If you can't    destroy a       skeleton with   your sword, try using a bomb.", // MSG_653 – Dialog28D – Owl
                                                                                         // Statue
        "To open a       treasure chest, use the pots    around it.", // MSG_654 – Dialog28E – Owl Statue
        "Hop on top of   the crystals to move forward.",              // MSG_655 – Dialog28F – Owl Statue
        "If you can't go over the poles, try throwing    things you have in your hands.", // MSG_656 – Dialog290 – Owl
                                                                                          // Statue
        "Jump off the    floor above to  reach the chest on the table.", // MSG_657 – Dialog291 – Owl Statue
        "To defeat the   monsters who    hold the key,   attack them froma higher place.", // MSG_658 – Dialog292 – Owl
                                                                                           // Statue
        "If the statue   looks strange,  shoot it with   the bow.", // MSG_659 – Dialog293 – Owl Statue
        "Let's take a    picture!            YES  NO<ask>",         // MSG_660 – Dialog294 – Photographer, Link
        "No picture?! Areyou pullin' my  leg?                Yes  No way<ask>", // MSG_661 – Dialog295 – Photographer,
                                                                                // Link
        "What a bummer!",                         // MSG_662 – Dialog296 – Photographer
        "Beautiful! I'll call this 'Game Over.'", // MSG_663 – Dialog297 – Photographer
        "What's your     name, young man?#####? Well     here's your     album, #####.   Give it a look  before you    "
        "  leave!",                                                               // MSG_664 – Dialog298 – Photographer
        "Let's see if we can fill that   album!",                                 // MSG_665 – Dialog299 – Photographer
        "11 shots left!  What kind of    picture should  I take?",                // MSG_666 – Dialog29A – Photographer
        "10 shots left!  What kind of    picture should  I take?",                // MSG_667 – Dialog29B – Photographer
        "9 shots left!   What kind of    picture should  I take?",                // MSG_668 – Dialog29C – Photographer
        "8 shots left!   What kind of    picture should  I take?",                // MSG_669 – Dialog29D – Photographer
        "7 shots left!   What kind of    picture should  I take?",                // MSG_670 – Dialog29E – Photographer
        "6 shots left!   What kind of    picture should  I take?",                // MSG_671 – Dialog29F – Photographer
        "5 shots left!   What kind of    picture should  I take?",                // MSG_672 – Dialog2A0 – Photographer
        "4 shots left!   What kind of    picture should  I take?",                // MSG_673 – Dialog2A1 – Photographer
        "3 shots left!   What kind of    picture should  I take?",                // MSG_674 – Dialog2A2 – Photographer
        "2 shots left!   What kind of    picture should  I take?",                // MSG_675 – Dialog2A3 – Photographer
        "1 shots left!   What kind of    picture should  I take?",                // MSG_676 – Dialog2A4 – Photographer
        "Oh no! You're   out of film!    Don't forget to look at your    album!", // MSG_677 – Dialog2A5 – Photographer
        "Hi! I'm the     photographer!   What a great    photo moment!   I'll call this  'Heads Up!'", // MSG_678 –
                                                                                                       // Dialog2A6 –
                                                                                                       // Photographer
        "Hey, this       represents your adventures      perfectly!", // MSG_679 – Dialog2A7 – Photographer
        "I'll call this  one 'Close      Call.' Hmm.",                // MSG_680 – Dialog2A8 – Photographer
        "I'm too close.",                                             // MSG_681 – Dialog2A9 – Photographer
        "I should back up.",                                          // MSG_682 – Dialog2AA – Photographer
        "Aaaaaah!",                                                   // MSG_683 – Dialog2AB – Photographer
        "I'm going back  to the store.   Bye!",                       // MSG_684 – Dialog2AC – Photographer, probably
        "See me later,   when you're     alone!",                     // MSG_685 – Dialog2AD – Photographer, probably
        "Are you sure?       YES  NO<ask>",                           // MSG_686 – Dialog2AE – Photographer, probably
        "Ah how I love   pictures. Hey,  #####! What are you doing here? ", // MSG_687 – Dialog2AF – Photographer,
                                                                            // probably

        // Credits
        // NewStaffRoles
        "    1998 STAFF    ", // MSG_688
        "    SUPERVISOR    ", // MSG_689
        "     DIRECTOR     ", // MSG_690
        "  SCRIPT WRITER   ", // MSG_691
        "    PROGRAMMER    ", // MSG_692
        "CHARACTER DESIGNER", // MSG_693
        "  SOUND COMPOSER  ", // MSG_694
        "     ART WORK     ", // MSG_695
        "TECHNICAL SUPPORT ", // MSG_696
        "  ENGLISH SCRIPT  ", // MSG_697
        "SPECIAL THANKS TO ", // MSG_698

        // DebugStaffRoles
        "   DEBUG STAFF    ", // MSG_699

        // OriginalStaffRoles
        "    1993 STAFF    ", // MSG_700
        " DUNGEON DESIGNER ", // MSG_701
        "   ILLUSTRATOR    ", // MSG_702
        "     PRODUCER     ", // MSG_703
        "EXECUTIVE PRODUCER", // MSG_704
        "                  ", // MSG_705

        // NewStaffPeople
        "                  ", // MSG_706
        "  TAKASHI TEZUKA  ", // MSG_707
        "YOSINORI TUTIYAMA ", // MSG_708
        " NOBUO MATSUMIYA  ", // MSG_709
        "    EIJI NOTO     ", // MSG_710
        "   KIYOSHI KODA   ", // MSG_711
        "SIGEHIRO KASAMATU ", // MSG_712
        "  MIKIO MISHIMA   ", // MSG_713
        "   KYOKO KIMURA   ", // MSG_714
        "   YUICHI OZAKI   ", // MSG_715
        "   KEIKO IZAWA    ", // MSG_716
        "   N KOGANEZAWA   ", // MSG_717
        "   JIM WORNELL    ", // MSG_718
        "   KEIKO TAMURA   ", // MSG_719
        "    TAMAYO ITO    ", // MSG_720
        "  AKIYA SAKAMOTO  ", // MSG_721
        " R&D2 DEBUG STAFF ", // MSG_722
        " SUPER MARIO CLUB ", // MSG_723
        "YASUHISA YAMAMURA ", // MSG_724
        "  KENSUKE TANABE  ", // MSG_725
        " YOSHIAKI KOIZUMI ", // MSG_726
        "  KAZUAKI MORITA  ", // MSG_727
        "TAKAMITSU KUZUHARA", // MSG_728
        " MASANAO ARIMOTO  ", // MSG_729
        "  SHIGEFUMI HINO  ", // MSG_730
        "  KAZUMI TOTAKA   ", // MSG_731
        "  MINAKO HAMANO   ", // MSG_732
        "  KOZUE ISHIKAWA  ", // MSG_733
        "  YOUICHI KOTABE  ", // MSG_734
        "    DAN OWSEN     ", // MSG_735
        " TOSHIHIKO NAKAGO ", // MSG_736
        "    KOJI KONDO    ", // MSG_737
        " TOMOAKI KUROUME  ", // MSG_738
        " MASAICHI OKUMURA ", // MSG_739
        "    KANAE WADA    ", // MSG_740
        " SHIGERU MIYAMOTO ", // MSG_741
        " HIROSHI YAMAUCHI ", // MSG_742
        "THE  END          "  // MSG_743
    }};
};

} // namespace zelda::core