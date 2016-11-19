#ifndef REVERSI_H
#define REVERSI_H

#include <iostream>
#include <limits>
#include <cassert>
#include <utility>
#include <tuple>
#include <vector>
#include <unordered_map>

using namespace std;

//#define DEBUG_SEARCH
#define USE_FLOAT
#define USE_RANDOM

#ifdef DEBUG_SEARCH
	#include <fstream>
	extern ofstream out;
#endif

#ifdef USE_RANDOM
	#include <random>
	extern default_random_engine engine;
#endif

typedef const bool& cbool;
typedef const short& cshort;
typedef const int& cint;
typedef const float& cfloat;

typedef unsigned long long brd_type;
typedef const brd_type& cbrd_type;
typedef unsigned char line_type;
typedef const line_type& cline_type;
typedef short pos_type;
typedef const pos_type& cpos_type;
#ifdef USE_FLOAT
	typedef float calc_type;
#else
	typedef short calc_type;
#endif
typedef const calc_type& ccalc_type;
enum chessman{blank,white,black,null};
//typedef const chessman& cchessman;
typedef chessman cchessman;

const calc_type inf = numeric_limits<short>::max();
const calc_type _inf = - inf;

enum method{
	mthd_default = 0x1,

	mthd_ab = 0x1, // alpha beta pruning
	mthd_pvs = 0x2, // principal variation search
	mthd_trans = 0x4, // transition table
	mthd_kill = 0x8, // killer heuristic
	mthd_mtdf = 0x10, // memory-enhanced test driver with node n and value f
	mthd_ids = 0x20, // iterative deepening search
	mthd_train = 0x40,
	mthd_ptn = 0x80
};
//typedef const method& cmethod;
typedef method cmethod;

enum sts_type{
	sts_null = 0x0,
	sts_black = 0x1,
	sts_white = 0x2,
	sts_turn = 0x4,
	sts_again = 0x8,
	sts_end = 0x10,

	sts_bwin = sts_black | sts_end,
	sts_wwin = sts_white | sts_end,
	sts_tie = sts_end,
	sts_bturn = sts_black | sts_turn,
	sts_wturn = sts_white | sts_turn,
	sts_bagain = sts_black | sts_again,
	sts_wagain = sts_white | sts_again
};

struct coordinate{
	coordinate():x(-1),y(-1){}
	coordinate(cpos_type _x,cpos_type _y):x(_x),y(_y){}
	pos_type x;
	pos_type y;
	void print()const{
		cout << '(' << x << ',' << y << ')';
	}
};
typedef const coordinate& ccoordinate;

class board;
namespace std{
	template <>
	struct hash<board>;
}
struct choice;

class board{
	friend struct hash<board>;
public:
	struct conf_score{
		calc_type *a,*b,*c;
	};
	typedef const conf_score& cconf_score;

	board(){};
	board(cbrd_type _brd_black,cbrd_type _brd_white)
		:brd_black(_brd_black),brd_white(_brd_white){}

	friend bool operator==(const board& b1,const board& b2){
		return (b1.brd_black == b2.brd_black) && (b1.brd_white == b2.brd_white);
	}

	static const brd_type last;
	static const pos_type chessman_num = 4;
	static const pos_type size = 8;
	static const pos_type size2 = size * size;
	static const char chr_print[chessman_num];
	enum pos_enum{pos_angle,pos_edge,pos_inner,pos_center};
	static const pos_type pos_num = 4;
	static const pos_type layer_num = 3;
	static const pos_type stage_num = 3;
	static const pos_type enum_num = 256;
	static const short max_height = 20;

	static calc_type (*fun)(const board& brd,cbool color);

	typedef pair<calc_type,calc_type> interval;

	static calc_type table_param[stage_num][pos_num];

	friend ostream& operator<<(ostream& out,const board& brd){
		brd.do_print(out);
		return out;
	}
	const board& print(ostream& out = cout)const{
		return do_print(out);
	}
	board& print(ostream& out = cout){
		do_print(out);
		return *this;
	}

	static void config();
	static conf_score stage_config(cpos_type stage){
		conf_score conf;
		if(stage < 0 || stage >= stage_num){
			cout << "Error: out of range\n";
			conf.a = conf.b = conf.c = 0;
			return conf;
		}
		static bool flag = true;
		if(flag){
			config();
			flag = false;
		}
		conf.a = table_eval[stage][0];
		conf.b = table_eval[stage][1];
		conf.c = table_eval[stage][2];
		return conf;
	}

	board& assign(cbrd_type _brd_black,cbrd_type _brd_white){
		brd_black = _brd_black;
		brd_white = _brd_white;
		return *this;
	}
	board& initial(){
		return this->assign(0x0000000810000000,0x0000001008000000);
	}
//	void tcl_initial(){
//		this->initial();
//	}
	brd_type bget(cbool color)const{
		if(color){
			return this->bget<true>();
		}else{
			return this->bget<false>();
		}
	}
//	int tcl_bget(cbool color,cbool is_high){
//		brd_type brd_blue = this->bget(color);
//		return int(is_high ? brd_blue >> 32 : brd_blue);
//	}
	chessman get(cpos_type x, cpos_type y)const{
		if(x < 0 || y < 0 || x >= size || y >= size){
			cout << "Error: out of range\n";
			return blank;
		}
		return get(brd_type(1) << ((y << 3) + x));
	}

	board& set(cpos_type x, cpos_type y, cchessman chsman){
		if(x < 0 || y < 0 || x >= size || y >= size){
			cout << "Error: out of range\n";
			return *this;
		}
		return set(brd_type(1) << ((y << 3) + x),chsman);
	}

	board& mirror(cbool is_horizontal);
	board& rotater(pos_type n90);
	board& rotatel(pos_type n90){
		return rotater(4 - n90);
	}

	bool flip(cbool color, cpos_type x, cpos_type y){
		if(x < 0 || y < 0 || x >= size || y >= size){
			cout << "Error: out of range\n";
			return false;
		}
		if(color){
			return flip<true>(brd_type(1) << ((y << 3) + x));
		}else{
			return flip<false>(brd_type(1) << ((y << 3) + x));
		}
	}
	calc_type count(cbool color)const{
		if(color){
			return count<true>();
		}else{
			return count<false>();
		}
	}
	static short count(cbrd_type brd){
		brd_type result = brd - ((brd >> 1) & 0x5555555555555555);
		result = (result & 0x3333333333333333)
			+ ((result >> 2) & 0x3333333333333333);
		result = (result + (result >> 4)) & 0x0F0F0F0F0F0F0F0F;
		return (result * 0x0101010101010101) >> 56;
	}
	brd_type get_move(cbool color) {
		if(color){
			return get_move<true>();
		}else{
			return get_move<false>();
		}
	}
	short count_move(cbool color){
		if(color){
			return count_move<true>();
		}else{
			return count_move<false>();
		}
	}
	calc_type sum()const{
		return count<true>() + count<false>();
	} 
	calc_type score(cbool color,cpos_type stage)const{
		conf_score conf = stage_config(stage);
		if(color){
			return score<true>(conf);
		}else{
			return score<false>(conf);
		}
	}
	calc_type search(
		cmethod mthd,cbool color,cshort height,ccalc_type alpha = _inf,
		ccalc_type beta = inf,ccalc_type acc = 0,cpos_type stage = 0,ccalc_type gamma = 0)const;
	vector<choice> get_choice(cmethod method,cbool color,cshort height,cpos_type stage = 0)const;
	static choice select_choice(vector<choice> choices,const float& variation = 0.75);
	coordinate play(cmethod mthd,cbool color,short height = -1,short stage = -1);
	sts_type get_status(cbool color){
		bool flag_black = (count_move(true) == 0);
		bool flag_white = (count_move(false) == 0);
		int num_diff = count(true) - count(false);
		if(color){
			if(flag_black){
				if(flag_white){
					if(num_diff){
						if(num_diff > 0){
							return sts_bwin;
						}else{
							return sts_wwin;
						}
					}else{
						return sts_tie;
					}
				}else{
					return sts_wagain;
				}
			}else{
				return sts_bturn;
			}
		}else{
			if(flag_white){
				if(flag_black){
					if(num_diff){
						if(num_diff > 0){
							return sts_bwin;
						}else{
							return sts_wwin;
						}
					}else{
						return sts_tie;
					}
				}else{
					return sts_bagain;
				}
			}else{
				return sts_wturn;
			}
		}
	}

protected:

	brd_type brd_black,brd_white;

	static const brd_type  lbound = 0xfefefefefefefefe;
	static const brd_type  rbound = 0x7f7f7f7f7f7f7f7f;
	static const brd_type  ubound = 0xffffffffffffff00;
	static const brd_type  dbound = 0x00ffffffffffffff;
	static const brd_type ulbound = 0xfefefefefefefe00;
	static const brd_type urbound = 0x7f7f7f7f7f7f7f00;
	static const brd_type dlbound = 0x00fefefefefefefe;
	static const brd_type drbound = 0x007f7f7f7f7f7f7f;

	static calc_type table_eval[stage_num][size][enum_num];
	static calc_type table_temp[2][board::max_height + 1][size2];

	const board& do_print(ostream& out = cout)const{
//		brd_type mask = 1;
//		for(pos_type i = 0;i != size;++i){
//			for(pos_type j = 0;j != size;++j){
//				out << chr_print[get(mask)];
//				mask <<= 1;
//			}
//			out << '\n';
//		}
		string s =
			"¨X¨T¨h¨T¨h¨T¨h¨T¨h¨T¨h¨T¨h¨T¨h¨T¨[\n"
			"¨U.©¦.©¦.©¦.©¦.©¦.©¦.©¦.¨U\n"
			"¨c©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤¨f\n"
			"¨U.©¦.©¦.©¦.©¦.©¦.©¦.©¦.¨U\n"
			"¨c©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤¨f\n"
			"¨U.©¦.©¦.©¦.©¦.©¦.©¦.©¦.¨U\n"
			"¨c©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤¨f\n"
			"¨U.©¦.©¦.©¦.©¦.©¦.©¦.©¦.¨U\n"
			"¨c©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤¨f\n"
			"¨U.©¦.©¦.©¦.©¦.©¦.©¦.©¦.¨U\n"
			"¨c©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤¨f\n"
			"¨U.©¦.©¦.©¦.©¦.©¦.©¦.©¦.¨U\n"
			"¨c©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤¨f\n"
			"¨U.©¦.©¦.©¦.©¦.©¦.©¦.©¦.¨U\n"
			"¨c©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤©à©¤¨f\n"
			"¨U.©¦.©¦.©¦.©¦.©¦.©¦.©¦.¨U\n"
			"¨^¨T¨k¨T¨k¨T¨k¨T¨k¨T¨k¨T¨k¨T¨k¨T¨a\n"
		;
		brd_type mask = 1;
		string::size_type pos;
		while((pos = s.find(".")) != s.npos){
			s.replace(pos,1,"  ");
		}
		for(pos_type i = 0;i != size;++i){
			for(pos_type j = 0;j != size;++j){
				s[i * 4 + j * 70 + 37] = chr_print[get(mask)];
				mask <<= 1;
			}
		}
		while((pos = s.find(".")) != s.npos){
			s.replace(pos,1," ");
		}
		while((pos = s.find("#")) != s.npos){
			s.replace(pos,2,"¡ñ");
		}
		while((pos = s.find("O")) != s.npos){
			s.replace(pos,2,"¡ð");
		}
		out << s;
		return *this;
	}

	template<bool color> inline
	brd_type& bget(){
		if(color){
			return brd_black;
		}else{
			return brd_white;
		}
	}
	template<bool color> inline
	const brd_type& bget()const{
		if(color){
			return brd_black;
		}else{
			return brd_white;
		}
	}

	inline chessman get(cbrd_type mask)const{
		if(mask & brd_black){
			if(mask & brd_white){
				return null;
			}else{
				return black;
			}
		}else{
			if(mask & brd_white){
				return white;
			}else{
				return blank;
			}
		}
	}
	template<bool color> inline
	board& set(cbrd_type mask, cbool flag){
		if(color){
			if(flag){
				brd_black |= mask;
			}else{
				brd_white &= ~mask;
			}
		}else{
			if(flag){
				brd_black |= mask;
			}else{
				brd_white &= ~mask;
			}
		}
		return *this;
	}
	inline board& set(cbrd_type mask, cchessman chsm){
		if(chsm & white){
			brd_white |= mask;
		}else{
			brd_white &= ~mask;
		}
		if(chsm & black){
			brd_black |= mask;
		}else{
			brd_black &= ~mask;
		}
		return *this;
	}

	template<bool color>
	bool flip(cbrd_type mask){

		#define up(mask) mask >>= 8
		#define down(mask) mask <<= 8
		#define left(mask) mask >>= 1
		#define right(mask) mask <<= 1
		#define uleft(mask) mask >>= 9
		#define uright(mask) mask >>= 7
		#define dleft(mask) mask <<= 7
		#define dright(mask) mask <<= 9

		if((brd_black | brd_white) & mask){
			return false;
		}
		bool everflip = false;
		brd_type pos = mask;
		brd_type& blue = bget<color>();
		brd_type& green = bget<!color>();
		while(pos & lbound){
			left(pos);
			if(green & pos)
				continue;
			if(blue & pos){
				while(right(pos), pos != mask){
					blue |= pos;
					green &= ~pos;
					everflip = true;
				}
			}
			break;
		}
		pos = mask;
		while(pos & rbound){
			right(pos);
			if(green & pos)
				continue;
			if(blue & pos){
				while(left(pos), pos != mask){
					blue |= pos;
					green &= ~pos;
					everflip = true;
				}
			}
			break;
		}
		pos = mask;
		while(pos & ubound){
			up(pos);
			if(green & pos)
				continue;
			if(blue & pos){
				while(down(pos), pos != mask){
					blue |= pos;
					green &= ~pos;
					everflip = true;
				}
			}
			break;
		}
		pos = mask;
		while(pos & dbound){
			down(pos);
			if(green & pos)
				continue;
			if(blue & pos){
				while(up(pos), pos != mask){
					blue |= pos;
					green &= ~pos;
					everflip = true;
				}
			}
			break;
		}
		pos = mask;
		while(pos & ulbound){
			uleft(pos);
			if(green & pos)
				continue;
			if(blue & pos){
				while(dright(pos), pos != mask){
					blue |= pos;
					green &= ~pos;
					everflip = true;
				}
			}
			break;
		}
		pos = mask;
		while(pos & urbound){
			uright(pos);
			if(green & pos)
				continue;
			if(blue & pos){
				while(dleft(pos), pos != mask){
					blue |= pos;
					green &= ~pos;
					everflip = true;
				}
			}
			break;
		}
		pos = mask;
		while(pos & dlbound){
			dleft(pos);
			if(green & pos)
				continue;
			if(blue & pos){
				while(uright(pos), pos != mask){
					blue |= pos;
					green &= ~pos;
					everflip = true;
				}
			}
			break;
		}
		pos = mask;
		while(pos & drbound){
			dright(pos);
			if(green & pos)
				continue;
			if(blue & pos){
				while(uleft(pos), pos != mask){
					blue |= pos;
					green &= ~pos;
					everflip = true;
				}
			}
			break;
		}
		if(everflip){
			blue |= mask;
			green &= ~mask;
		}
		return everflip;
	}
	template<bool color>
	short count()const{
		return count(bget<color>());
	}
	template<bool color>
	brd_type get_move()const{
		const brd_type& brd_blue = bget<color>();
		const brd_type& brd_green = bget<!color>();
		brd_type moves;
		brd_type brd_green_inner;
		brd_type brd_flip;
		brd_type brd_green_adj;

		brd_green_inner = brd_green & 0x7E7E7E7E7E7E7E7Eu;

		brd_flip = (brd_blue >> 1) & brd_green_inner;
		brd_flip |= (brd_flip >> 1) & brd_green_inner;

		brd_green_adj = brd_green_inner & (brd_green_inner >> 1);
		brd_flip |= (brd_flip >> 2) & brd_green_adj;
		brd_flip |= (brd_flip >> 2) & brd_green_adj;

		moves = brd_flip >> 1;

		brd_flip = (brd_blue << 1) & brd_green_inner;
		brd_flip |= (brd_flip << 1) & brd_green_inner;

		brd_green_adj = brd_green_inner & (brd_green_inner << 1);
		brd_flip |= (brd_flip << 2) & brd_green_adj;
		brd_flip |= (brd_flip << 2) & brd_green_adj;

		moves |= brd_flip << 1;

		brd_flip = (brd_blue >> 8) & brd_green;
		brd_flip |= (brd_flip >> 8) & brd_green;

		brd_green_adj = brd_green & (brd_green >> 8);
		brd_flip |= (brd_flip >> 16) & brd_green_adj;
		brd_flip |= (brd_flip >> 16) & brd_green_adj;

		moves |= brd_flip >> 8;

		brd_flip = (brd_blue << 8) & brd_green;
		brd_flip |= (brd_flip << 8) & brd_green;

		brd_green_adj = brd_green & (brd_green << 8);
		brd_flip |= (brd_flip << 16) & brd_green_adj;
		brd_flip |= (brd_flip << 16) & brd_green_adj;

		moves |= brd_flip << 8;

		brd_flip = (brd_blue >> 7) & brd_green_inner;
		brd_flip |= (brd_flip >> 7) & brd_green_inner;
		
		brd_green_adj = brd_green_inner & (brd_green_inner >> 7);
		brd_flip |= (brd_flip >> 14) & brd_green_adj;
		brd_flip |= (brd_flip >> 14) & brd_green_adj;
		
		moves |= brd_flip >> 7;

		brd_flip = (brd_blue << 7) & brd_green_inner;
		brd_flip |= (brd_flip << 7) & brd_green_inner;

		brd_green_adj = brd_green_inner & (brd_green_inner << 7);
		brd_flip |= (brd_flip << 14) & brd_green_adj;
		brd_flip |= (brd_flip << 14) & brd_green_adj;

		moves |= brd_flip << 7;

		brd_flip = (brd_blue >> 9) & brd_green_inner;
		brd_flip |= (brd_flip >> 9) & brd_green_inner;
		
		brd_green_adj = brd_green_inner & (brd_green_inner >> 9);
		brd_flip |= (brd_flip >> 18) & brd_green_adj;
		brd_flip |= (brd_flip >> 18) & brd_green_adj;
		
		moves |= brd_flip >> 9;
		
		brd_flip = (brd_blue << 9) & brd_green_inner;
		brd_flip |= (brd_flip << 9) & brd_green_inner;

		brd_green_adj = brd_green_inner & (brd_green_inner << 9);
		brd_flip |= (brd_flip << 18) & brd_green_adj;
		brd_flip |= (brd_flip << 18) & brd_green_adj;

		moves |= brd_flip << 9;

		moves &= ~(brd_blue | brd_green);
		return moves;
	}
	template<bool color>
	short count_move()const{
		return count(get_move<color>());
	}
	template<bool color> inline
	calc_type score(cconf_score conf)const{

		brd_type blue = bget<color>();
		brd_type green = bget<!color>();
		calc_type result;

		result = conf.a[(unsigned char&)blue]; blue >>= size;
		result += conf.b[(unsigned char&)blue]; blue >>= size;
		result += conf.c[(unsigned char&)blue]; blue >>= size;
		result += conf.c[(unsigned char&)blue]; blue >>= size;
		result += conf.c[(unsigned char&)blue]; blue >>= size;
		result += conf.c[(unsigned char&)blue]; blue >>= size;
		result += conf.b[(unsigned char&)blue]; blue >>= size;
		result += conf.a[(unsigned char&)blue];

		result -= conf.a[(unsigned char&)green]; green >>= size;
		result -= conf.b[(unsigned char&)green]; green >>= size;
		result -= conf.c[(unsigned char&)green]; green >>= size;
		result -= conf.c[(unsigned char&)green]; green >>= size;
		result -= conf.c[(unsigned char&)green]; green >>= size;
		result -= conf.c[(unsigned char&)green]; green >>= size;
		result -= conf.b[(unsigned char&)green]; green >>= size;
		result -= conf.a[(unsigned char&)green];

		return result;
	}

	#ifdef USE_FLOAT
		static const calc_type mark_max;
	#else
		static const calc_type mark_max = 10000;
	#endif

	template<bool color,method mthd>
	calc_type search(
		cshort height,ccalc_type alpha,ccalc_type beta,
		ccalc_type acc,cconf_score conf,ccalc_type gamma = 0)const{
		if(mthd & mthd_ptn){
			return search_ptn<color>(height,alpha,beta);
		}if(mthd & mthd_train){
			return search_train<color>(height,alpha,beta,acc,conf);
		}else if(mthd & mthd_mtdf){
			return search_mtd<color>(height,alpha,beta,acc,conf,gamma);
		}else if(mthd & mthd_trans){
			return search_trans<color>(height,alpha,beta,acc,conf);
		}else if(mthd & mthd_pvs){
			return search_pvs<color>(height,alpha,beta,acc,conf);
		}else if(mthd & mthd_ab){
			return search<color>(height,alpha,beta,acc,conf);
		}else{
			assert(false);
			return 0;
		}
	};
	template<bool color>
	calc_type search(cshort height,calc_type alpha,calc_type beta,calc_type acc,cconf_score conf)const;
	template<bool color>
	calc_type search_train(cshort height,calc_type alpha,calc_type beta,calc_type acc,cconf_score conf)const;
	template<bool color>
	calc_type search_pvs(cshort height,calc_type alpha,calc_type beta,calc_type acc,cconf_score conf)const;
	template<bool color>
	calc_type search_trans(cshort height,calc_type alpha,calc_type beta,calc_type acc,cconf_score conf)const;
	template<bool color>
	calc_type search_mtd(
		cshort height,calc_type alpha,calc_type beta,
		ccalc_type acc,cconf_score conf,calc_type gamma
	)const;
	template<bool color>
	float search_ptn(cshort height,float alpha,float beta)const;
	
	template<bool color,method mthd>
	vector<choice> get_choice(cshort height,cconf_score conf,ccalc_type gamma = 0)const;

	template<bool color>
	float score_ptn()const;

public:
	template<bool color,bool is_win>
	void adjust_ptn()const;

	void refresh_ptn()const;
};

template <>
struct hash<board> : public unary_function<board, size_t>{
	size_t operator()(const board& brd) const{
		return (
			size_t(brd.brd_black)
			+ size_t(brd.brd_black >> 32) * 1867970917
			+ size_t(brd.brd_white) * 1009562269
			+ size_t(brd.brd_white >> 32) * 739351663
		);
	}
};

struct brd_val{
	board brd;
	pos_type pos;
	calc_type val;
	friend inline bool operator<(const brd_val& b1,const brd_val& b2){
		return b1.val < b2.val;
	}
	friend inline bool operator>(const brd_val& b1,const brd_val& b2){
		return b1.val > b2.val;
	}
};

struct choice{
	float val;
	board brd;
	pos_type x;
	pos_type y;
	float rnd_val;
	void print()const{
		cout << '(' << val << ',' << x << ',' << y << ')';
	}
};

void print(const vector<choice>& choices);

#endif // REVERSI_H
