#ifndef BITPEROCTAVELUTS_H
#define BITPEROCTAVELUTS_H
#include <stdint.h>

const uint16_t twoPowers12bit[4096] = {
0, 11, 22, 33, 44, 55, 67, 78, 89, 100, 111, 122, 133, 144, 155, 167, 178, 189, 200, 211, 222, 233, 244, 256, 267, 278, 289, 300, 311, 322, 334, 345, 356, 367, 378, 389, 400, 412, 423, 434, 445, 456, 467, 479, 490, 501, 512, 523, 535, 546, 557, 568, 579, 590, 602, 613, 624, 635, 646, 658, 669, 680, 691, 702, 714, 725, 736, 747, 758, 770, 781, 792, 803, 815, 826, 837, 848, 860, 871, 882, 893, 905, 916, 927, 938, 949, 961, 972, 983, 995, 1006, 1017, 1028, 1040, 1051, 1062, 1073, 1085, 1096, 1107, 1118, 1130, 1141, 1152, 1164, 1175, 1186, 1197, 1209, 1220, 1231, 1243, 1254, 1265, 1277, 1288, 1299, 1311, 1322, 1333, 1344, 1356, 1367, 1378, 1390, 1401, 1412, 1424, 1435, 1446, 1458, 1469, 1480, 1492, 1503, 1514, 1526, 1537, 1548, 1560, 1571, 1583, 1594, 1605, 1617, 1628, 1639, 1651, 1662, 1673, 1685, 1696, 1708, 1719, 1730, 1742, 1753, 1765, 1776, 1787, 1799, 1810, 1821, 1833, 1844, 1856, 1867, 1879, 1890, 1901, 1913, 1924, 1936, 1947, 1958, 1970, 1981, 1993, 2004, 2016, 2027, 2038, 2050, 2061, 2073, 2084, 2096, 2107, 2119, 2130, 2141, 2153, 2164, 2176, 2187, 2199, 2210, 2222, 2233, 2245, 2256, 2268, 2279, 2290, 2302, 2313, 2325, 2336, 2348, 2359, 2371, 2382, 2394, 2405, 2417, 2428, 2440, 2451, 2463, 2474, 2486, 2497, 2509, 2520, 2532, 2543, 2555, 2566, 2578, 2590, 2601, 2613, 2624, 2636, 2647, 2659, 2670, 2682, 2693, 2705, 2716, 2728, 2740, 2751, 2763, 2774, 2786, 2797, 2809, 2821, 2832, 2844, 2855, 2867, 2878, 2890, 2902, 2913, 2925, 2936, 2948, 2959, 2971, 2983, 2994, 3006, 3017, 3029, 3041, 3052, 3064, 3075, 3087, 3099, 3110, 3122, 3134, 3145, 3157, 3168, 3180, 3192, 3203, 3215, 3227, 3238, 3250, 3261, 3273, 3285, 3296, 3308, 3320, 3331, 3343, 3355, 3366, 3378, 3390, 3401, 3413, 3425, 3436, 3448, 3460, 3471, 3483, 3495, 3506, 3518, 3530, 3541, 3553, 3565, 3577, 3588, 3600, 3612, 3623, 3635, 3647, 3658, 3670, 3682, 3694, 3705, 3717, 3729, 3740, 3752, 3764, 3776, 3787, 3799, 3811, 3823, 3834, 3846, 3858, 3870, 3881, 3893, 3905, 3917, 3928, 3940, 3952, 3964, 3975, 3987, 3999, 4011, 4022, 4034, 4046, 4058, 4070, 4081, 4093, 4105, 4117, 4128, 4140, 4152, 4164, 4176, 4187, 4199, 4211, 4223, 4235, 4246, 4258, 4270, 4282, 4294, 4305, 4317, 4329, 4341, 4353, 4365, 4376, 4388, 4400, 4412, 4424, 4436, 4447, 4459, 4471, 4483, 4495, 4507, 4519, 4530, 4542, 4554, 4566, 4578, 4590, 4602, 4613, 4625, 4637, 4649, 4661, 4673, 4685, 4697, 4709, 4720, 4732, 4744, 4756, 4768, 4780, 4792, 4804, 4816, 4827, 4839, 4851, 4863, 4875, 4887, 4899, 4911, 4923, 4935, 4947, 4959, 4971, 4982, 4994, 5006, 5018, 5030, 5042, 5054, 5066, 5078, 5090, 5102, 5114, 5126, 5138, 5150, 5162, 5174, 5186, 5198, 5210, 5222, 5233, 5245, 5257, 5269, 5281, 5293, 5305, 5317, 5329, 5341, 5353, 5365, 5377, 5389, 5401, 5413, 5425, 5437, 5449, 5461, 5473, 5485, 5497, 5509, 5521, 5534, 5546, 5558, 5570, 5582, 5594, 5606, 5618, 5630, 5642, 5654, 5666, 5678, 5690, 5702, 5714, 5726, 5738, 5750, 5762, 5774, 5787, 5799, 5811, 5823, 5835, 5847, 5859, 5871, 5883, 5895, 5907, 5919, 5932, 5944, 5956, 5968, 5980, 5992, 6004, 6016, 6028, 6040, 6053, 6065, 6077, 6089, 6101, 6113, 6125, 6137, 6150, 6162, 6174, 6186, 6198, 6210, 6222, 6235, 6247, 6259, 6271, 6283, 6295, 6307, 6320, 6332, 6344, 6356, 6368, 6380, 6393, 6405, 6417, 6429, 6441, 6453, 6466, 6478, 6490, 6502, 6514, 6527, 6539, 6551, 6563, 6575, 6588, 6600, 6612, 6624, 6636, 6649, 6661, 6673, 6685, 6698, 6710, 6722, 6734, 6746, 6759, 6771, 6783, 6795, 6808, 6820, 6832, 6844, 6857, 6869, 6881, 6893, 6906, 6918, 6930, 6942, 6955, 6967, 6979, 6991, 7004, 7016, 7028, 7041, 7053, 7065, 7077, 7090, 7102, 7114, 7127, 7139, 7151, 7164, 7176, 7188, 7200, 7213, 7225, 7237, 7250, 7262, 7274, 7287, 7299, 7311, 7324, 7336, 7348, 7361, 7373, 7385, 7398, 7410, 7422, 7435, 7447, 7459, 7472, 7484, 7496, 7509, 7521, 7534, 7546, 7558, 7571, 7583, 7595, 7608, 7620, 7633, 7645, 7657, 7670, 7682, 7694, 7707, 7719, 7732, 7744, 7756, 7769, 7781, 7794, 7806, 7818, 7831, 7843, 7856, 7868, 7881, 7893, 7905, 7918, 7930, 7943, 7955, 7968, 7980, 7992, 8005, 8017, 8030, 8042, 8055, 8067, 8080, 8092, 8105, 8117, 8129, 8142, 8154, 8167, 8179, 8192, 8204, 8217, 8229, 8242, 8254, 8267, 8279, 8292, 8304, 8317, 8329, 8342, 8354, 8367, 8379, 8392, 8404, 8417, 8429, 8442, 8454, 8467, 8479, 8492, 8504, 8517, 8529, 8542, 8555, 8567, 8580, 8592, 8605, 8617, 8630, 8642, 8655, 8667, 8680, 8693, 8705, 8718, 8730, 8743, 8755, 8768, 8781, 8793, 8806, 8818, 8831, 8843, 8856, 8869, 8881, 8894, 8906, 8919, 8932, 8944, 8957, 8969, 8982, 8995, 9007, 9020, 9033, 9045, 9058, 9070, 9083, 9096, 9108, 9121, 9134, 9146, 9159, 9171, 9184, 9197, 9209, 9222, 9235, 9247, 9260, 9273, 9285, 9298, 9311, 9323, 9336, 9349, 9361, 9374, 9387, 9399, 9412, 9425, 9437, 9450, 9463, 9476, 9488, 9501, 9514, 9526, 9539, 9552, 9564, 9577, 9590, 9603, 9615, 9628, 9641, 9653, 9666, 9679, 9692, 9704, 9717, 9730, 9743, 9755, 9768, 9781, 9794, 9806, 9819, 9832, 9845, 9857, 9870, 9883, 9896, 9908, 9921, 9934, 9947, 9959, 9972, 9985, 9998, 10011, 10023, 10036, 10049, 10062, 10074, 10087, 10100, 10113, 10126, 10138, 10151, 10164, 10177, 10190, 10203, 10215, 10228, 10241, 10254, 10267, 10279, 10292, 10305, 10318, 10331, 10344, 10357, 10369, 10382, 10395, 10408, 10421, 10434, 10446, 10459, 10472, 10485, 10498, 10511, 10524, 10537, 10549, 10562, 10575, 10588, 10601, 10614, 10627, 10640, 10652, 10665, 10678, 10691, 10704, 10717, 10730, 10743, 10756, 10769, 10782, 10794, 10807, 10820, 10833, 10846, 10859, 10872, 10885, 10898, 10911, 10924, 10937, 10950, 10963, 10975, 10988, 11001, 11014, 11027, 11040, 11053, 11066, 11079, 11092, 11105, 11118, 11131, 11144, 11157, 11170, 11183, 11196, 11209, 11222, 11235, 11248, 11261, 11274, 11287, 11300, 11313, 11326, 11339, 11352, 11365, 11378, 11391, 11404, 11417, 11430, 11443, 11456, 11469, 11482, 11495, 11508, 11521, 11534, 11547, 11560, 11573, 11586, 11600, 11613, 11626, 11639, 11652, 11665, 11678, 11691, 11704, 11717, 11730, 11743, 11756, 11769, 11782, 11796, 11809, 11822, 11835, 11848, 11861, 11874, 11887, 11900, 11913, 11927, 11940, 11953, 11966, 11979, 11992, 12005, 12018, 12031, 12045, 12058, 12071, 12084, 12097, 12110, 12123, 12137, 12150, 12163, 12176, 12189, 12202, 12215, 12229, 12242, 12255, 12268, 12281, 12294, 12308, 12321, 12334, 12347, 12360, 12374, 12387, 12400, 12413, 12426, 12439, 12453, 12466, 12479, 12492, 12505, 12519, 12532, 12545, 12558, 12572, 12585, 12598, 12611, 12624, 12638, 12651, 12664, 12677, 12691, 12704, 12717, 12730, 12744, 12757, 12770, 12783, 12797, 12810, 12823, 12836, 12850, 12863, 12876, 12889, 12903, 12916, 12929, 12942, 12956, 12969, 12982, 12996, 13009, 13022, 13036, 13049, 13062, 13075, 13089, 13102, 13115, 13129, 13142, 13155, 13169, 13182, 13195, 13209, 13222, 13235, 13249, 13262, 13275, 13289, 13302, 13315, 13329, 13342, 13355, 13369, 13382, 13395, 13409, 13422, 13435, 13449, 13462, 13476, 13489, 13502, 13516, 13529, 13542, 13556, 13569, 13583, 13596, 13609, 13623, 13636, 13650, 13663, 13676, 13690, 13703, 13717, 13730, 13743, 13757, 13770, 13784, 13797, 13810, 13824, 13837, 13851, 13864, 13878, 13891, 13905, 13918, 13931, 13945, 13958, 13972, 13985, 13999, 14012, 14026, 14039, 14053, 14066, 14080, 14093, 14106, 14120, 14133, 14147, 14160, 14174, 14187, 14201, 14214, 14228, 14241, 14255, 14268, 14282, 14295, 14309, 14322, 14336, 14349, 14363, 14376, 14390, 14404, 14417, 14431, 14444, 14458, 14471, 14485, 14498, 14512, 14525, 14539, 14552, 14566, 14580, 14593, 14607, 14620, 14634, 14647, 14661, 14675, 14688, 14702, 14715, 14729, 14742, 14756, 14770, 14783, 14797, 14810, 14824, 14838, 14851, 14865, 14878, 14892, 14906, 14919, 14933, 14946, 14960, 14974, 14987, 15001, 15015, 15028, 15042, 15055, 15069, 15083, 15096, 15110, 15124, 15137, 15151, 15165, 15178, 15192, 15206, 15219, 15233, 15247, 15260, 15274, 15288, 15301, 15315, 15329, 15342, 15356, 15370, 15383, 15397, 15411, 15425, 15438, 15452, 15466, 15479, 15493, 15507, 15521, 15534, 15548, 15562, 15575, 15589, 15603, 15617, 15630, 15644, 15658, 15672, 15685, 15699, 15713, 15727, 15740, 15754, 15768, 15782, 15795, 15809, 15823, 15837, 15850, 15864, 15878, 15892, 15906, 15919, 15933, 15947, 15961, 15974, 15988, 16002, 16016, 16030, 16043, 16057, 16071, 16085, 16099, 16112, 16126, 16140, 16154, 16168, 16182, 16195, 16209, 16223, 16237, 16251, 16265, 16278, 16292, 16306, 16320, 16334, 16348, 16362, 16375, 16389, 16403, 16417, 16431, 16445, 16459, 16473, 16486, 16500, 16514, 16528, 16542, 16556, 16570, 16584, 16598, 16611, 16625, 16639, 16653, 16667, 16681, 16695, 16709, 16723, 16737, 16751, 16764, 16778, 16792, 16806, 16820, 16834, 16848, 16862, 16876, 16890, 16904, 16918, 16932, 16946, 16960, 16974, 16988, 17002, 17016, 17030, 17044, 17057, 17071, 17085, 17099, 17113, 17127, 17141, 17155, 17169, 17183, 17197, 17211, 17225, 17239, 17253, 17267, 17281, 17295, 17309, 17323, 17337, 17352, 17366, 17380, 17394, 17408, 17422, 17436, 17450, 17464, 17478, 17492, 17506, 17520, 17534, 17548, 17562, 17576, 17590, 17604, 17618, 17633, 17647, 17661, 17675, 17689, 17703, 17717, 17731, 17745, 17759, 17773, 17787, 17802, 17816, 17830, 17844, 17858, 17872, 17886, 17900, 17914, 17929, 17943, 17957, 17971, 17985, 17999, 18013, 18028, 18042, 18056, 18070, 18084, 18098, 18112, 18127, 18141, 18155, 18169, 18183, 18197, 18212, 18226, 18240, 18254, 18268, 18282, 18297, 18311, 18325, 18339, 18353, 18368, 18382, 18396, 18410, 18424, 18439, 18453, 18467, 18481, 18495, 18510, 18524, 18538, 18552, 18567, 18581, 18595, 18609, 18624, 18638, 18652, 18666, 18681, 18695, 18709, 18723, 18738, 18752, 18766, 18780, 18795, 18809, 18823, 18837, 18852, 18866, 18880, 18895, 18909, 18923, 18937, 18952, 18966, 18980, 18995, 19009, 19023, 19038, 19052, 19066, 19081, 19095, 19109, 19124, 19138, 19152, 19167, 19181, 19195, 19210, 19224, 19238, 19253, 19267, 19281, 19296, 19310, 19324, 19339, 19353, 19367, 19382, 19396, 19411, 19425, 19439, 19454, 19468, 19482, 19497, 19511, 19526, 19540, 19554, 19569, 19583, 19598, 19612, 19626, 19641, 19655, 19670, 19684, 19699, 19713, 19727, 19742, 19756, 19771, 19785, 19800, 19814, 19828, 19843, 19857, 19872, 19886, 19901, 19915, 19930, 19944, 19959, 19973, 19987, 20002, 20016, 20031, 20045, 20060, 20074, 20089, 20103, 20118, 20132, 20147, 20161, 20176, 20190, 20205, 20219, 20234, 20248, 20263, 20277, 20292, 20306, 20321, 20336, 20350, 20365, 20379, 20394, 20408, 20423, 20437, 20452, 20466, 20481, 20496, 20510, 20525, 20539, 20554, 20568, 20583, 20598, 20612, 20627, 20641, 20656, 20670, 20685, 20700, 20714, 20729, 20743, 20758, 20773, 20787, 20802, 20816, 20831, 20846, 20860, 20875, 20890, 20904, 20919, 20933, 20948, 20963, 20977, 20992, 21007, 21021, 21036, 21051, 21065, 21080, 21095, 21109, 21124, 21139, 21153, 21168, 21183, 21197, 21212, 21227, 21241, 21256, 21271, 21285, 21300, 21315, 21329, 21344, 21359, 21374, 21388, 21403, 21418, 21432, 21447, 21462, 21477, 21491, 21506, 21521, 21535, 21550, 21565, 21580, 21594, 21609, 21624, 21639, 21653, 21668, 21683, 21698, 21712, 21727, 21742, 21757, 21772, 21786, 21801, 21816, 21831, 21845, 21860, 21875, 21890, 21905, 21919, 21934, 21949, 21964, 21979, 21993, 22008, 22023, 22038, 22053, 22068, 22082, 22097, 22112, 22127, 22142, 22157, 22171, 22186, 22201, 22216, 22231, 22246, 22260, 22275, 22290, 22305, 22320, 22335, 22350, 22365, 22379, 22394, 22409, 22424, 22439, 22454, 22469, 22484, 22498, 22513, 22528, 22543, 22558, 22573, 22588, 22603, 22618, 22633, 22648, 22663, 22677, 22692, 22707, 22722, 22737, 22752, 22767, 22782, 22797, 22812, 22827, 22842, 22857, 22872, 22887, 22902, 22917, 22932, 22947, 22962, 22977, 22991, 23006, 23021, 23036, 23051, 23066, 23081, 23096, 23111, 23126, 23141, 23156, 23171, 23186, 23201, 23216, 23232, 23247, 23262, 23277, 23292, 23307, 23322, 23337, 23352, 23367, 23382, 23397, 23412, 23427, 23442, 23457, 23472, 23487, 23502, 23517, 23532, 23548, 23563, 23578, 23593, 23608, 23623, 23638, 23653, 23668, 23683, 23698, 23714, 23729, 23744, 23759, 23774, 23789, 23804, 23819, 23834, 23850, 23865, 23880, 23895, 23910, 23925, 23940, 23955, 23971, 23986, 24001, 24016, 24031, 24046, 24062, 24077, 24092, 24107, 24122, 24137, 24153, 24168, 24183, 24198, 24213, 24229, 24244, 24259, 24274, 24289, 24304, 24320, 24335, 24350, 24365, 24381, 24396, 24411, 24426, 24441, 24457, 24472, 24487, 24502, 24518, 24533, 24548, 24563, 24579, 24594, 24609, 24624, 24640, 24655, 24670, 24685, 24701, 24716, 24731, 24746, 24762, 24777, 24792, 24808, 24823, 24838, 24853, 24869, 24884, 24899, 24915, 24930, 24945, 24961, 24976, 24991, 25007, 25022, 25037, 25053, 25068, 25083, 25099, 25114, 25129, 25145, 25160, 25175, 25191, 25206, 25221, 25237, 25252, 25267, 25283, 25298, 25314, 25329, 25344, 25360, 25375, 25390, 25406, 25421, 25437, 25452, 25467, 25483, 25498, 25514, 25529, 25544, 25560, 25575, 25591, 25606, 25622, 25637, 25652, 25668, 25683, 25699, 25714, 25730, 25745, 25760, 25776, 25791, 25807, 25822, 25838, 25853, 25869, 25884, 25900, 25915, 25931, 25946, 25962, 25977, 25993, 26008, 26023, 26039, 26054, 26070, 26085, 26101, 26117, 26132, 26148, 26163, 26179, 26194, 26210, 26225, 26241, 26256, 26272, 26287, 26303, 26318, 26334, 26349, 26365, 26381, 26396, 26412, 26427, 26443, 26458, 26474, 26490, 26505, 26521, 26536, 26552, 26567, 26583, 26599, 26614, 26630, 26645, 26661, 26677, 26692, 26708, 26723, 26739, 26755, 26770, 26786, 26801, 26817, 26833, 26848, 26864, 26880, 26895, 26911, 26927, 26942, 26958, 26974, 26989, 27005, 27021, 27036, 27052, 27068, 27083, 27099, 27115, 27130, 27146, 27162, 27177, 27193, 27209, 27224, 27240, 27256, 27271, 27287, 27303, 27319, 27334, 27350, 27366, 27381, 27397, 27413, 27429, 27444, 27460, 27476, 27492, 27507, 27523, 27539, 27555, 27570, 27586, 27602, 27618, 27633, 27649, 27665, 27681, 27696, 27712, 27728, 27744, 27760, 27775, 27791, 27807, 27823, 27839, 27854, 27870, 27886, 27902, 27918, 27933, 27949, 27965, 27981, 27997, 28013, 28028, 28044, 28060, 28076, 28092, 28108, 28123, 28139, 28155, 28171, 28187, 28203, 28219, 28234, 28250, 28266, 28282, 28298, 28314, 28330, 28346, 28361, 28377, 28393, 28409, 28425, 28441, 28457, 28473, 28489, 28505, 28521, 28536, 28552, 28568, 28584, 28600, 28616, 28632, 28648, 28664, 28680, 28696, 28712, 28728, 28744, 28760, 28776, 28791, 28807, 28823, 28839, 28855, 28871, 28887, 28903, 28919, 28935, 28951, 28967, 28983, 28999, 29015, 29031, 29047, 29063, 29079, 29095, 29111, 29127, 29143, 29159, 29175, 29191, 29207, 29223, 29240, 29256, 29272, 29288, 29304, 29320, 29336, 29352, 29368, 29384, 29400, 29416, 29432, 29448, 29464, 29480, 29496, 29513, 29529, 29545, 29561, 29577, 29593, 29609, 29625, 29641, 29657, 29674, 29690, 29706, 29722, 29738, 29754, 29770, 29786, 29803, 29819, 29835, 29851, 29867, 29883, 29899, 29916, 29932, 29948, 29964, 29980, 29996, 30012, 30029, 30045, 30061, 30077, 30093, 30110, 30126, 30142, 30158, 30174, 30191, 30207, 30223, 30239, 30255, 30272, 30288, 30304, 30320, 30336, 30353, 30369, 30385, 30401, 30418, 30434, 30450, 30466, 30483, 30499, 30515, 30531, 30548, 30564, 30580, 30596, 30613, 30629, 30645, 30661, 30678, 30694, 30710, 30727, 30743, 30759, 30775, 30792, 30808, 30824, 30841, 30857, 30873, 30890, 30906, 30922, 30939, 30955, 30971, 30988, 31004, 31020, 31037, 31053, 31069, 31086, 31102, 31118, 31135, 31151, 31167, 31184, 31200, 31217, 31233, 31249, 31266, 31282, 31298, 31315, 31331, 31348, 31364, 31380, 31397, 31413, 31430, 31446, 31462, 31479, 31495, 31512, 31528, 31545, 31561, 31577, 31594, 31610, 31627, 31643, 31660, 31676, 31693, 31709, 31725, 31742, 31758, 31775, 31791, 31808, 31824, 31841, 31857, 31874, 31890, 31907, 31923, 31940, 31956, 31973, 31989, 32006, 32022, 32039, 32055, 32072, 32088, 32105, 32121, 32138, 32154, 32171, 32187, 32204, 32220, 32237, 32254, 32270, 32287, 32303, 32320, 32336, 32353, 32369, 32386, 32403, 32419, 32436, 32452, 32469, 32485, 32502, 32519, 32535, 32552, 32568, 32585, 32602, 32618, 32635, 32652, 32668, 32685, 32701, 32718, 32735, 32751, 32768, 32785, 32801, 32818, 32834, 32851, 32868, 32884, 32901, 32918, 32934, 32951, 32968, 32984, 33001, 33018, 33034, 33051, 33068, 33084, 33101, 33118, 33135, 33151, 33168, 33185, 33201, 33218, 33235, 33252, 33268, 33285, 33302, 33318, 33335, 33352, 33369, 33385, 33402, 33419, 33436, 33452, 33469, 33486, 33503, 33519, 33536, 33553, 33570, 33586, 33603, 33620, 33637, 33654, 33670, 33687, 33704, 33721, 33738, 33754, 33771, 33788, 33805, 33822, 33838, 33855, 33872, 33889, 33906, 33922, 33939, 33956, 33973, 33990, 34007, 34024, 34040, 34057, 34074, 34091, 34108, 34125, 34142, 34158, 34175, 34192, 34209, 34226, 34243, 34260, 34277, 34293, 34310, 34327, 34344, 34361, 34378, 34395, 34412, 34429, 34446, 34463, 34479, 34496, 34513, 34530, 34547, 34564, 34581, 34598, 34615, 34632, 34649, 34666, 34683, 34700, 34717, 34734, 34751, 34768, 34785, 34802, 34819, 34836, 34852, 34869, 34886, 34903, 34920, 34937, 34954, 34971, 34988, 35006, 35023, 35040, 35057, 35074, 35091, 35108, 35125, 35142, 35159, 35176, 35193, 35210, 35227, 35244, 35261, 35278, 35295, 35312, 35329, 35346, 35363, 35381, 35398, 35415, 35432, 35449, 35466, 35483, 35500, 35517, 35534, 35551, 35569, 35586, 35603, 35620, 35637, 35654, 35671, 35688, 35706, 35723, 35740, 35757, 35774, 35791, 35808, 35826, 35843, 35860, 35877, 35894, 35911, 35928, 35946, 35963, 35980, 35997, 36014, 36032, 36049, 36066, 36083, 36100, 36118, 36135, 36152, 36169, 36186, 36204, 36221, 36238, 36255, 36272, 36290, 36307, 36324, 36341, 36359, 36376, 36393, 36410, 36428, 36445, 36462, 36479, 36497, 36514, 36531, 36548, 36566, 36583, 36600, 36618, 36635, 36652, 36669, 36687, 36704, 36721, 36739, 36756, 36773, 36791, 36808, 36825, 36843, 36860, 36877, 36895, 36912, 36929, 36947, 36964, 36981, 36999, 37016, 37033, 37051, 37068, 37085, 37103, 37120, 37138, 37155, 37172, 37190, 37207, 37224, 37242, 37259, 37277, 37294, 37311, 37329, 37346, 37364, 37381, 37399, 37416, 37433, 37451, 37468, 37486, 37503, 37521, 37538, 37555, 37573, 37590, 37608, 37625, 37643, 37660, 37678, 37695, 37713, 37730, 37747, 37765, 37782, 37800, 37817, 37835, 37852, 37870, 37887, 37905, 37922, 37940, 37957, 37975, 37992, 38010, 38028, 38045, 38063, 38080, 38098, 38115, 38133, 38150, 38168, 38185, 38203, 38220, 38238, 38256, 38273, 38291, 38308, 38326, 38343, 38361, 38379, 38396, 38414, 38431, 38449, 38467, 38484, 38502, 38519, 38537, 38555, 38572, 38590, 38607, 38625, 38643, 38660, 38678, 38696, 38713, 38731, 38749, 38766, 38784, 38802, 38819, 38837, 38854, 38872, 38890, 38908, 38925, 38943, 38961, 38978, 38996, 39014, 39031, 39049, 39067, 39084, 39102, 39120, 39138, 39155, 39173, 39191, 39208, 39226, 39244, 39262, 39279, 39297, 39315, 39333, 39350, 39368, 39386, 39404, 39421, 39439, 39457, 39475, 39492, 39510, 39528, 39546, 39564, 39581, 39599, 39617, 39635, 39652, 39670, 39688, 39706, 39724, 39742, 39759, 39777, 39795, 39813, 39831, 39848, 39866, 39884, 39902, 39920, 39938, 39956, 39973, 39991, 40009, 40027, 40045, 40063, 40081, 40098, 40116, 40134, 40152, 40170, 40188, 40206, 40224, 40242, 40259, 40277, 40295, 40313, 40331, 40349, 40367, 40385, 40403, 40421, 40439, 40457, 40475, 40492, 40510, 40528, 40546, 40564, 40582, 40600, 40618, 40636, 40654, 40672, 40690, 40708, 40726, 40744, 40762, 40780, 40798, 40816, 40834, 40852, 40870, 40888, 40906, 40924, 40942, 40960, 40978, 40996, 41014, 41032, 41050, 41068, 41086, 41104, 41122, 41140, 41158, 41176, 41195, 41213, 41231, 41249, 41267, 41285, 41303, 41321, 41339, 41357, 41375, 41393, 41411, 41430, 41448, 41466, 41484, 41502, 41520, 41538, 41556, 41574, 41593, 41611, 41629, 41647, 41665, 41683, 41701, 41720, 41738, 41756, 41774, 41792, 41810, 41829, 41847, 41865, 41883, 41901, 41919, 41938, 41956, 41974, 41992, 42010, 42029, 42047, 42065, 42083, 42101, 42120, 42138, 42156, 42174, 42193, 42211, 42229, 42247, 42265, 42284, 42302, 42320, 42338, 42357, 42375, 42393, 42412, 42430, 42448, 42466, 42485, 42503, 42521, 42539, 42558, 42576, 42594, 42613, 42631, 42649, 42668, 42686, 42704, 42723, 42741, 42759, 42777, 42796, 42814, 42833, 42851, 42869, 42888, 42906, 42924, 42943, 42961, 42979, 42998, 43016, 43034, 43053, 43071, 43090, 43108, 43126, 43145, 43163, 43181, 43200, 43218, 43237, 43255, 43274, 43292, 43310, 43329, 43347, 43366, 43384, 43402, 43421, 43439, 43458, 43476, 43495, 43513, 43532, 43550, 43569, 43587, 43605, 43624, 43642, 43661, 43679, 43698, 43716, 43735, 43753, 43772, 43790, 43809, 43827, 43846, 43864, 43883, 43901, 43920, 43938, 43957, 43975, 43994, 44013, 44031, 44050, 44068, 44087, 44105, 44124, 44142, 44161, 44180, 44198, 44217, 44235, 44254, 44272, 44291, 44310, 44328, 44347, 44365, 44384, 44403, 44421, 44440, 44458, 44477, 44496, 44514, 44533, 44551, 44570, 44589, 44607, 44626, 44645, 44663, 44682, 44701, 44719, 44738, 44757, 44775, 44794, 44813, 44831, 44850, 44869, 44887, 44906, 44925, 44943, 44962, 44981, 45000, 45018, 45037, 45056, 45074, 45093, 45112, 45131, 45149, 45168, 45187, 45205, 45224, 45243, 45262, 45280, 45299, 45318, 45337, 45355, 45374, 45393, 45412, 45431, 45449, 45468, 45487, 45506, 45525, 45543, 45562, 45581, 45600, 45619, 45637, 45656, 45675, 45694, 45713, 45731, 45750, 45769, 45788, 45807, 45826, 45844, 45863, 45882, 45901, 45920, 45939, 45958, 45976, 45995, 46014, 46033, 46052, 46071, 46090, 46109, 46128, 46146, 46165, 46184, 46203, 46222, 46241, 46260, 46279, 46298, 46317, 46336, 46355, 46373, 46392, 46411, 46430, 46449, 46468, 46487, 46506, 46525, 46544, 46563, 46582, 46601, 46620, 46639, 46658, 46677, 46696, 46715, 46734, 46753, 46772, 46791, 46810, 46829, 46848, 46867, 46886, 46905, 46924, 46943, 46962, 46981, 47000, 47019, 47038, 47057, 47076, 47095, 47114, 47134, 47153, 47172, 47191, 47210, 47229, 47248, 47267, 47286, 47305, 47324, 47343, 47363, 47382, 47401, 47420, 47439, 47458, 47477, 47496, 47516, 47535, 47554, 47573, 47592, 47611, 47630, 47650, 47669, 47688, 47707, 47726, 47745, 47765, 47784, 47803, 47822, 47841, 47860, 47880, 47899, 47918, 47937, 47956, 47976, 47995, 48014, 48033, 48052, 48072, 48091, 48110, 48129, 48149, 48168, 48187, 48206, 48226, 48245, 48264, 48283, 48303, 48322, 48341, 48360, 48380, 48399, 48418, 48438, 48457, 48476, 48495, 48515, 48534, 48553, 48573, 48592, 48611, 48631, 48650, 48669, 48689, 48708, 48727, 48747, 48766, 48785, 48805, 48824, 48843, 48863, 48882, 48901, 48921, 48940, 48960, 48979, 48998, 49018, 49037, 49056, 49076, 49095, 49115, 49134, 49153, 49173, 49192, 49212, 49231, 49251, 49270, 49289, 49309, 49328, 49348, 49367, 49387, 49406, 49425, 49445, 49464, 49484, 49503, 49523, 49542, 49562, 49581, 49601, 49620, 49640, 49659, 49679, 49698, 49718, 49737, 49757, 49776, 49796, 49815, 49835, 49854, 49874, 49893, 49913, 49932, 49952, 49971, 49991, 50011, 50030, 50050, 50069, 50089, 50108, 50128, 50148, 50167, 50187, 50206, 50226, 50245, 50265, 50285, 50304, 50324, 50343, 50363, 50383, 50402, 50422, 50442, 50461, 50481, 50500, 50520, 50540, 50559, 50579, 50599, 50618, 50638, 50658, 50677, 50697, 50717, 50736, 50756, 50776, 50795, 50815, 50835, 50854, 50874, 50894, 50914, 50933, 50953, 50973, 50992, 51012, 51032, 51052, 51071, 51091, 51111, 51131, 51150, 51170, 51190, 51210, 51229, 51249, 51269, 51289, 51308, 51328, 51348, 51368, 51387, 51407, 51427, 51447, 51467, 51486, 51506, 51526, 51546, 51566, 51586, 51605, 51625, 51645, 51665, 51685, 51704, 51724, 51744, 51764, 51784, 51804, 51824, 51843, 51863, 51883, 51903, 51923, 51943, 51963, 51983, 52002, 52022, 52042, 52062, 52082, 52102, 52122, 52142, 52162, 52182, 52202, 52221, 52241, 52261, 52281, 52301, 52321, 52341, 52361, 52381, 52401, 52421, 52441, 52461, 52481, 52501, 52521, 52541, 52561, 52581, 52601, 52621, 52641, 52661, 52681, 52701, 52721, 52741, 52761, 52781, 52801, 52821, 52841, 52861, 52881, 52901, 52921, 52941, 52961, 52981, 53001, 53021, 53041, 53061, 53081, 53102, 53122, 53142, 53162, 53182, 53202, 53222, 53242, 53262, 53282, 53302, 53323, 53343, 53363, 53383, 53403, 53423, 53443, 53463, 53484, 53504, 53524, 53544, 53564, 53584, 53605, 53625, 53645, 53665, 53685, 53705, 53726, 53746, 53766, 53786, 53806, 53827, 53847, 53867, 53887, 53907, 53928, 53948, 53968, 53988, 54008, 54029, 54049, 54069, 54089, 54110, 54130, 54150, 54170, 54191, 54211, 54231, 54251, 54272, 54292, 54312, 54333, 54353, 54373, 54393, 54414, 54434, 54454, 54475, 54495, 54515, 54536, 54556, 54576, 54597, 54617, 54637, 54658, 54678, 54698, 54719, 54739, 54759, 54780, 54800, 54820, 54841, 54861, 54882, 54902, 54922, 54943, 54963, 54983, 55004, 55024, 55045, 55065, 55085, 55106, 55126, 55147, 55167, 55188, 55208, 55228, 55249, 55269, 55290, 55310, 55331, 55351, 55372, 55392, 55412, 55433, 55453, 55474, 55494, 55515, 55535, 55556, 55576, 55597, 55617, 55638, 55658, 55679, 55699, 55720, 55740, 55761, 55781, 55802, 55823, 55843, 55864, 55884, 55905, 55925, 55946, 55966, 55987, 56008, 56028, 56049, 56069, 56090, 56110, 56131, 56152, 56172, 56193, 56213, 56234, 56255, 56275, 56296, 56316, 56337, 56358, 56378, 56399, 56420, 56440, 56461, 56481, 56502, 56523, 56543, 56564, 56585, 56605, 56626, 56647, 56667, 56688, 56709, 56730, 56750, 56771, 56792, 56812, 56833, 56854, 56874, 56895, 56916, 56937, 56957, 56978, 56999, 57020, 57040, 57061, 57082, 57103, 57123, 57144, 57165, 57186, 57206, 57227, 57248, 57269, 57289, 57310, 57331, 57352, 57373, 57393, 57414, 57435, 57456, 57477, 57497, 57518, 57539, 57560, 57581, 57602, 57622, 57643, 57664, 57685, 57706, 57727, 57748, 57768, 57789, 57810, 57831, 57852, 57873, 57894, 57915, 57935, 57956, 57977, 57998, 58019, 58040, 58061, 58082, 58103, 58124, 58145, 58166, 58186, 58207, 58228, 58249, 58270, 58291, 58312, 58333, 58354, 58375, 58396, 58417, 58438, 58459, 58480, 58501, 58522, 58543, 58564, 58585, 58606, 58627, 58648, 58669, 58690, 58711, 58732, 58753, 58774, 58795, 58816, 58837, 58858, 58879, 58900, 58921, 58943, 58964, 58985, 59006, 59027, 59048, 59069, 59090, 59111, 59132, 59153, 59174, 59196, 59217, 59238, 59259, 59280, 59301, 59322, 59343, 59365, 59386, 59407, 59428, 59449, 59470, 59491, 59513, 59534, 59555, 59576, 59597, 59618, 59640, 59661, 59682, 59703, 59724, 59746, 59767, 59788, 59809, 59830, 59852, 59873, 59894, 59915, 59937, 59958, 59979, 60000, 60021, 60043, 60064, 60085, 60106, 60128, 60149, 60170, 60192, 60213, 60234, 60255, 60277, 60298, 60319, 60341, 60362, 60383, 60405, 60426, 60447, 60468, 60490, 60511, 60532, 60554, 60575, 60596, 60618, 60639, 60661, 60682, 60703, 60725, 60746, 60767, 60789, 60810, 60831, 60853, 60874, 60896, 60917, 60938, 60960, 60981, 61003, 61024, 61045, 61067, 61088, 61110, 61131, 61153, 61174, 61196, 61217, 61238, 61260, 61281, 61303, 61324, 61346, 61367, 61389, 61410, 61432, 61453, 61475, 61496, 61518, 61539, 61561, 61582, 61604, 61625, 61647, 61668, 61690, 61711, 61733, 61754, 61776, 61797, 61819, 61841, 61862, 61884, 61905, 61927, 61948, 61970, 61992, 62013, 62035, 62056, 62078, 62099, 62121, 62143, 62164, 62186, 62208, 62229, 62251, 62272, 62294, 62316, 62337, 62359, 62381, 62402, 62424, 62446, 62467, 62489, 62511, 62532, 62554, 62576, 62597, 62619, 62641, 62662, 62684, 62706, 62727, 62749, 62771, 62793, 62814, 62836, 62858, 62879, 62901, 62923, 62945, 62966, 62988, 63010, 63032, 63053, 63075, 63097, 63119, 63140, 63162, 63184, 63206, 63228, 63249, 63271, 63293, 63315, 63337, 63358, 63380, 63402, 63424, 63446, 63468, 63489, 63511, 63533, 63555, 63577, 63599, 63620, 63642, 63664, 63686, 63708, 63730, 63752, 63774, 63795, 63817, 63839, 63861, 63883, 63905, 63927, 63949, 63971, 63993, 64014, 64036, 64058, 64080, 64102, 64124, 64146, 64168, 64190, 64212, 64234, 64256, 64278, 64300, 64322, 64344, 64366, 64388, 64410, 64432, 64454, 64476, 64498, 64520, 64542, 64564, 64586, 64608, 64630, 64652, 64674, 64696, 64718, 64740, 64762, 64784, 64806, 64828, 64850, 64872, 64894, 64916, 64938, 64961, 64983, 65005, 65027, 65049, 65071, 65093, 65115, 65137, 65159, 65182, 65204, 65226, 65248, 65270, 65292, 65314, 65337, 65359, 65381, 65403, 65425, 65447, 65469, 65492, 65514
};

//const uint32_t towPowers1_2q16_16[4096]

const float note2bpo[129] = {
 0.709432, 0.7927653333, 0.8760986667, 0.959432, 1.0427653333, 1.1260986667, 1.209432, 1.2927653333, 1.3760986667, 1.459432, 1.5427653333, 1.6260986667, 1.709432, 1.7927653333,
 1.8760986667, 1.959432, 2.0427653333, 2.1260986667, 2.209432, 2.2927653333, 2.3760986667, 2.459432, 2.5427653333, 2.6260986667, 2.709432, 2.7927653333, 2.8760986667, 2.959432,
 3.0427653333, 3.1260986667, 3.209432, 3.2927653333, 3.3760986667, 3.459432, 3.5427653333, 3.6260986667, 3.709432, 3.7927653333, 3.8760986667, 3.959432, 4.0427653333, 4.1260986667,
 4.209432, 4.2927653333, 4.3760986667, 4.459432, 4.5427653333, 4.6260986667, 4.709432, 4.7927653333, 4.8760986667, 4.959432, 5.0427653333, 5.1260986667, 5.209432, 5.2927653333,
 5.3760986667, 5.459432, 5.5427653333, 5.6260986667, 5.709432, 5.7927653333, 5.8760986667, 5.959432, 6.0427653333, 6.1260986667, 6.209432, 6.2927653333, 6.3760986667, 6.459432,
 6.5427653333, 6.6260986667, 6.709432, 6.7927653333, 6.8760986667, 6.959432, 7.0427653333, 7.1260986667, 7.209432, 7.2927653333, 7.3760986667, 7.459432, 7.5427653333, 7.6260986667,
 7.709432, 7.7927653333, 7.8760986667, 7.959432, 8.0427653333, 8.1260986667, 8.209432, 8.2927653333, 8.3760986667, 8.459432, 8.5427653333, 8.6260986667, 8.709432, 8.7927653333,
 8.8760986667, 8.959432, 9.0427653333, 9.1260986667, 9.209432, 9.2927653333, 9.3760986667, 9.459432, 9.5427653333, 9.6260986667, 9.709432, 9.7927653333, 9.8760986667, 9.959432,
 10.0427653333, 10.1260986667, 10.209432, 10.2927653333, 10.3760986667, 10.459432, 10.5427653333, 10.6260986667, 10.709432, 10.7927653333, 10.8760986667, 10.959432, 11.0427653333,
 11.1260986667, 11.209432, 11.2927653333, 11.3760986667

};

#endif