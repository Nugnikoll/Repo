#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>

#include "board.h"
#include "search.h"

default_random_engine engine(
	chrono::system_clock::now().time_since_epoch().count()
);

const pos_type board::size;
const pos_type board::size2;

val_type board::table_param[65][8] = {
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,-0.208331,0.000000,-0.069444,-0.208331},
	{0.000000,0.000000,0.000000,0.000000,-0.355528,0.000000,0.000000},
	{0.000000,0.000000,0.000000,-0.367572,0.595313,-0.649682,-0.367572},
	{0.000000,0.000000,-1.531175,0.984567,0.129213,-3.690223,-0.546608},
	{0.000000,0.975918,-7.726622,2.924005,0.643114,-0.278880,-3.826698},
	{4.905859,-0.472400,-9.027919,0.300450,0.533726,-1.057358,-1.047993},
	{16.376923,-2.426331,-11.086559,-1.617266,0.634245,-0.273602,0.665945},
	{20.584538,-0.720083,-9.876479,-0.133319,0.590140,-0.854930,-0.672170},
	{21.003420,-0.547758,-9.518813,0.051998,0.613661,-0.299980,-1.026146},
	{20.912933,-0.469987,-9.800544,-0.144348,0.633554,-0.762021,-0.696981},
	{20.117504,-0.953491,-10.119866,-0.515124,0.669253,-0.380664,-0.412926},
	{20.101736,-0.692768,-9.968653,-0.415323,0.636286,-0.638408,-0.460422},
	{20.118116,-0.669180,-9.756088,-0.231661,0.643962,-0.290679,-0.739793},
	{20.824991,-0.464635,-9.923014,-0.243292,0.651043,-0.554024,-0.642850},
	{20.646828,-0.531416,-9.681949,-0.213224,0.683727,-0.335452,-0.744713},
	{20.753765,-0.460696,-9.561624,-0.098902,0.649610,-0.402098,-0.826134},
	{20.294188,-0.556728,-9.612317,-0.244679,0.717876,-0.340472,-0.672559},
	{20.580173,-0.522293,-9.611416,-0.145493,0.681845,-0.293825,-0.782507},
	{20.349457,-0.616407,-9.333259,-0.143066,0.694173,-0.144592,-0.820825},
	{20.513315,-0.609721,-9.410192,-0.141186,0.709089,-0.174588,-0.806400},
	{20.426132,-0.513640,-9.275916,-0.186977,0.700583,-0.108256,-0.791428},
	{20.373199,-0.623244,-9.147242,-0.065894,0.663960,0.057856,-0.937844},
	{20.073374,-0.511514,-8.960539,-0.053318,0.707782,0.100143,-0.949025},
	{20.074343,-0.608586,-8.795899,0.059712,0.686826,0.189077,-1.074373},
	{20.106535,-0.429830,-8.636664,0.056733,0.686022,0.195711,-1.064929},
	{19.983170,-0.374173,-8.339124,0.104331,0.708193,0.199064,-1.113689},
	{19.601143,-0.449437,-8.271505,0.096150,0.700751,0.396005,-1.111633},
	{19.617695,-0.321362,-8.098276,0.152658,0.681873,0.317880,-1.181220},
	{19.192276,-0.373001,-7.895928,0.142606,0.696553,0.436078,-1.149765},
	{18.728336,-0.383193,-7.531145,0.166771,0.698484,0.463221,-1.192729},
	{18.598209,-0.259041,-7.232648,0.226356,0.685271,0.511099,-1.260870},
	{18.231495,-0.304453,-6.939572,0.138456,0.775170,0.475245,-1.151845},
	{17.809965,-0.230462,-6.667944,0.155353,0.688056,0.547828,-1.225492},
	{17.247864,-0.287637,-6.453121,0.182520,0.739710,0.589503,-1.215905},
	{16.846474,-0.168737,-5.916312,0.170477,0.764657,0.571999,-1.227266},
	{16.444130,-0.216100,-5.698105,0.173437,0.791164,0.584813,-1.198367},
	{15.719388,-0.266581,-5.421880,0.130694,0.809707,0.706024,-1.177222},
	{15.320999,-0.235548,-5.025248,0.171217,0.834629,0.709212,-1.200455},
	{14.825852,-0.170099,-4.796511,0.147921,0.851595,0.727780,-1.192573},
	{14.247610,-0.239360,-4.513853,0.147290,0.862820,0.777360,-1.147536},
	{13.742138,-0.125886,-3.938438,0.162436,1.033051,0.714810,-1.155527},
	{13.339836,-0.165622,-3.697773,0.156101,1.012541,0.731500,-1.144873},
	{12.667105,-0.059371,-3.320290,0.136678,1.076281,0.734437,-1.146204},
	{12.202864,-0.071734,-3.053338,0.122226,1.061846,0.733687,-1.152171},
	{11.489226,0.049540,-2.697289,0.136968,1.117074,0.703645,-1.154277},
	{10.878270,-0.019649,-2.534574,0.091301,1.133652,0.748238,-1.098961},
	{10.128412,-0.016931,-2.077768,0.079193,1.318724,0.741735,-1.040836},
	{9.393907,-0.026549,-1.896556,0.063495,1.259409,0.771248,-1.046707},
	{8.605281,0.011441,-1.589774,0.035396,1.372201,0.782655,-1.001935},
	{7.674734,0.000081,-1.358644,0.021157,1.359152,0.839687,-1.038120},
	{6.720123,0.013689,-1.095915,-0.046139,1.344346,0.876617,-1.020547},
	{5.787610,-0.043346,-0.813347,-0.083092,1.436681,0.942385,-0.958419},
	{4.748230,-0.015112,-0.720632,-0.128759,1.441239,0.969549,-0.922242},
	{3.535244,-0.069550,-0.548139,-0.216595,1.353092,1.081835,-0.889387},
	{2.351599,-0.037536,-0.489021,-0.282886,1.311074,1.119514,-0.855005},
	{1.035332,-0.131475,-0.345415,-0.379934,1.190677,1.273898,-0.670691},
	{0.999757,-0.315792,-0.594843,-0.417358,1.255734,1.349686,-0.657163},
	{0.315366,-0.435131,-0.583755,-0.473077,1.686792,1.473132,-0.432544},
	{-0.759675,-0.608137,-0.905610,-0.708815,2.908651,1.712582,-0.144662},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000}
};

void board::config(const string& file_param){
	config_flip();
	config_search();

	if(file_param.size()){
		ifstream in(file_param, ios::in | ios::binary);
		if(in){
			in.read((char*)table_param, sizeof(table_param));
		}
	}
}

string board::to_string()const{
	string s =
		"╔═╤═╤═╤═╤═╤═╤═╤═╗\n"
		"║ │ │ │ │ │ │ │ ║\n"
		"╟─┼─┼─┼─┼─┼─┼─┼─╢\n"
		"║ │ │ │ │ │ │ │ ║\n"
		"╟─┼─┼─┼─┼─┼─┼─┼─╢\n"
		"║ │ │ │ │ │ │ │ ║\n"
		"╟─┼─┼─┼─┼─┼─┼─┼─╢\n"
		"║ │ │ │ │ │ │ │ ║\n"
		"╟─┼─┼─┼─┼─┼─┼─┼─╢\n"
		"║ │ │ │ │ │ │ │ ║\n"
		"╟─┼─┼─┼─┼─┼─┼─┼─╢\n"
		"║ │ │ │ │ │ │ │ ║\n"
		"╟─┼─┼─┼─┼─┼─┼─┼─╢\n"
		"║ │ │ │ │ │ │ │ ║\n"
		"╟─┼─┼─┼─┼─┼─┼─┼─╢\n"
		"║ │ │ │ │ │ │ │ ║\n"
		"╚═╧═╧═╧═╧═╧═╧═╧═╝\n"
	;

	pos_type pos = 0;
	string result;

	for(char& chr:s){
		if(chr == ' '){
			switch(get(pos)){
			case blank:
				result += " ";
				break;
			case black:
				result += "●";
				break;
			case white:
				result += "○";
				break;
			case null:
				result += "╳";
				break;
			default:
				result += "╳";
				break;
			}
			++pos;
		}else{
			result += chr;
		}
	}

	return result;
}

choice board::select_choice(vector<choice> choices, const float& factor){
	int length = choices.size();
	float *arr = new float[length];

	float m = _inf;
	for(const choice& c: choices){
		m = max(m, c.beta);
	}
	for(int i = 0; i != length; ++i){
		arr[i] = pow(factor, choices[i].beta - m);
	}

	discrete_distribution<short> dist(arr, arr + length);
	choice best = choices[dist(engine)];
	delete arr;

	return best;
}

choice board::play(cmethod mthd, cbool color, cshort depth){

	vector<choice> choices = get_choice(mthd, color, depth);
	if(choices.empty()){
		return choice{board(), _inf, inf, -1};
	}else{
		choice best;
		if(mthd == mthd_rnd){
			uniform_int_distribution<int> scatter(0, choices.size() - 1);
			best = choices[scatter(engine)];
		}else{
			best = select_choice(choices);
		}
		flip(color, best.pos);
		return best;
	}
}

void board::play_out(cmethod mthd, bool color, cshort depth){
	board brd = *this;
	bool flag = true, flag_next = true;
	pos_type pos;

	while(flag || flag_next){
		auto p_mthd = process_method(mthd, depth);
		pos = play(p_mthd.first, color, p_mthd.second).pos;
		color = !color;
		flag = flag_next;
		flag_next = (pos >= 0);
		brd = *this;
	}
}
