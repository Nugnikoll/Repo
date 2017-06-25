#include <algorithm>

#include "reversi.h"
#include "pattern.h"

calc_type table_val[board::size2][board::size2];
calc_type alpha_save, beta_save;
typedef unordered_map<board,board::interval> trans_type;
trans_type trans_table;
trans_type::iterator trans_ptr;

void board::config_search(){}

calc_type board::search(
	cmethod mthd,cbool color,cshort height,
	ccalc_type alpha,ccalc_type beta,ccalc_type gamma
)const{

	if(height < 0){
		short total = this->sum();
		if(total <= 7){
			height = 9;
		}else if(total <= 10){
			height = 8;
		}else if(total <= size2 - 22){
			height = 7;
		}else if(total <= size2 - 15){
			height = 8;
		}else{
			height = 20;
		}
	}

	/*
		// This part of code is generated by:

		str = ["mthd_ab","mthd_kill","mthd_pvs","mthd_trans","mthd_ptn"];

		size = len(str);
		length = 1 << size;

		result = "";
		for i in range(length):
			s = [];
			for j in range(size):
				if i & (1 << j):
					s += [str[j]];
			s = (
				"case " + "|".join(s) + " :\n"
				+ "\treturn board::search<method(" + "|".join(s) + ")>(color,height,alpha,beta);\n"
			);
			result += s;

		print(result);
	*/

	switch(mthd){
	case mthd_rnd :
		return board::search<method(mthd_rnd)>(color,height,alpha,beta);
	case mthd_ab :
		return board::search<method(mthd_ab)>(color,height,alpha,beta);
	case mthd_kill :
		return board::search<method(mthd_kill)>(color,height,alpha,beta);
	case mthd_ab|mthd_kill :
		return board::search<method(mthd_ab|mthd_kill)>(color,height,alpha,beta);
	case mthd_pvs :
		return board::search<method(mthd_pvs)>(color,height,alpha,beta);
	case mthd_ab|mthd_pvs :
		return board::search<method(mthd_ab|mthd_pvs)>(color,height,alpha,beta);
	case mthd_kill|mthd_pvs :
		return board::search<method(mthd_kill|mthd_pvs)>(color,height,alpha,beta);
	case mthd_ab|mthd_kill|mthd_pvs :
		return board::search<method(mthd_ab|mthd_kill|mthd_pvs)>(color,height,alpha,beta);
	case mthd_trans :
		return board::search<method(mthd_trans)>(color,height,alpha,beta);
	case mthd_ab|mthd_trans :
		return board::search<method(mthd_ab|mthd_trans)>(color,height,alpha,beta);
	case mthd_kill|mthd_trans :
		return board::search<method(mthd_kill|mthd_trans)>(color,height,alpha,beta);
	case mthd_ab|mthd_kill|mthd_trans :
		return board::search<method(mthd_ab|mthd_kill|mthd_trans)>(color,height,alpha,beta);
	case mthd_pvs|mthd_trans :
		return board::search<method(mthd_pvs|mthd_trans)>(color,height,alpha,beta);
	case mthd_ab|mthd_pvs|mthd_trans :
		return board::search<method(mthd_ab|mthd_pvs|mthd_trans)>(color,height,alpha,beta);
	case mthd_kill|mthd_pvs|mthd_trans :
		return board::search<method(mthd_kill|mthd_pvs|mthd_trans)>(color,height,alpha,beta);
	case mthd_ab|mthd_kill|mthd_pvs|mthd_trans :
		return board::search<method(mthd_ab|mthd_kill|mthd_pvs|mthd_trans)>(color,height,alpha,beta);
	case mthd_ptn :
		return board::search<method(mthd_ptn)>(color,height,alpha,beta);
	case mthd_ab|mthd_ptn :
		return board::search<method(mthd_ab|mthd_ptn)>(color,height,alpha,beta);
	case mthd_kill|mthd_ptn :
		return board::search<method(mthd_kill|mthd_ptn)>(color,height,alpha,beta);
	case mthd_ab|mthd_kill|mthd_ptn :
		return board::search<method(mthd_ab|mthd_kill|mthd_ptn)>(color,height,alpha,beta);
	case mthd_pvs|mthd_ptn :
		return board::search<method(mthd_pvs|mthd_ptn)>(color,height,alpha,beta);
	case mthd_ab|mthd_pvs|mthd_ptn :
		return board::search<method(mthd_ab|mthd_pvs|mthd_ptn)>(color,height,alpha,beta);
	case mthd_kill|mthd_pvs|mthd_ptn :
		return board::search<method(mthd_kill|mthd_pvs|mthd_ptn)>(color,height,alpha,beta);
	case mthd_ab|mthd_kill|mthd_pvs|mthd_ptn :
		return board::search<method(mthd_ab|mthd_kill|mthd_pvs|mthd_ptn)>(color,height,alpha,beta);
	case mthd_trans|mthd_ptn :
		return board::search<method(mthd_trans|mthd_ptn)>(color,height,alpha,beta);
	case mthd_ab|mthd_trans|mthd_ptn :
		return board::search<method(mthd_ab|mthd_trans|mthd_ptn)>(color,height,alpha,beta);
	case mthd_kill|mthd_trans|mthd_ptn :
		return board::search<method(mthd_kill|mthd_trans|mthd_ptn)>(color,height,alpha,beta);
	case mthd_ab|mthd_kill|mthd_trans|mthd_ptn :
		return board::search<method(mthd_ab|mthd_kill|mthd_trans|mthd_ptn)>(color,height,alpha,beta);
	case mthd_pvs|mthd_trans|mthd_ptn :
		return board::search<method(mthd_pvs|mthd_trans|mthd_ptn)>(color,height,alpha,beta);
	case mthd_ab|mthd_pvs|mthd_trans|mthd_ptn :
		return board::search<method(mthd_ab|mthd_pvs|mthd_trans|mthd_ptn)>(color,height,alpha,beta);
	case mthd_kill|mthd_pvs|mthd_trans|mthd_ptn :
		return board::search<method(mthd_kill|mthd_pvs|mthd_trans|mthd_ptn)>(color,height,alpha,beta);
	case mthd_ab|mthd_kill|mthd_pvs|mthd_trans|mthd_ptn :
		return board::search<method(mthd_ab|mthd_kill|mthd_pvs|mthd_trans|mthd_ptn)>(color,height,alpha,beta);
	default:
		assert(false);
		return 0;
	}

};

template<method mthd>
calc_type board::search(cbool color,cshort height,calc_type alpha,calc_type beta)const{

	#ifdef DEBUG_SEARCH
	auto fun = [&]()->calc_type{
	#endif

	if(mthd == mthd_rnd){
		return 0;
	}else{

		if(mthd & mthd_trans){
			trans_ptr = trans_table.find(*this);
			if(trans_ptr != trans_table.end()){
				auto& trans_interval = trans_ptr->second;
				if(trans_interval.first >= beta){
					return trans_interval.first;
					//return beta;
				}
				if(trans_interval.second <= alpha){
					return trans_interval.second;
					//return alpha;
				}
				if(trans_interval.first > alpha){
					alpha = trans_interval.first;
				}
				if(trans_interval.second < beta){
					beta = trans_interval.second;
				}
				assert(alpha <= beta);
			}else{
				trans_ptr = trans_table.insert(
					std::make_pair(*this,interval(_inf,inf))
				).first;
			}
			alpha_save = alpha;
			beta_save = beta;
		}

		if(height == 0){
			if(mthd & mthd_ptn)
				return this->score_ptn(color);
			else
				return this->score(color);
		}

		board brd;
		calc_type result;
		pos_type table_pos[size2];
		calc_type* ptr_val = table_val[this->sum()];
		bool flag_flip = false;
		const method mthd_temp = method(mthd & ~mthd_pvs);

		for(pos_type i = 0;i != size2;++i){
			table_pos[i] = i;
		}
		if(mthd & mthd_kill){
			sort(table_pos,table_pos + size2,
				[&ptr_val](cpos_type p1,cpos_type p2) -> bool{
					return ptr_val[p1] > ptr_val[p2];
				}
			);
		}

		brd = *this;
		for(cpos_type pos:table_pos){
			if(brd.flip(color,pos)){
				if(mthd & mthd_pvs){
					if(flag_flip){
						result = - brd.search<mthd_temp>(!color,height - 1,-alpha - 1,-alpha);
						if(result > alpha && result < beta)
							result = - brd.search<mthd>(!color,height - 1,-beta,-alpha);
					}else{
						result = - brd.search<mthd>(!color,height - 1,-beta,-alpha);
					}
				}else{
					result = - brd.search<mthd>(!color,height - 1,-beta,-alpha);
				}
				if(mthd & mthd_kill){
					ptr_val[pos] = result;
				}
				if(result >= beta){
					return beta;
				}
				if(result > alpha){
					alpha = result;
				}
				brd = *this;
				flag_flip = true;
			}
		}
		
		if(!flag_flip){
			reverse(table_pos,table_pos + size2);

			for(cpos_type pos:table_pos){
				if(brd.flip(!color,pos)){
					if(mthd & mthd_pvs){
						if(flag_flip){
							result = brd.search<mthd_temp>(color,height - 1,beta - 1,beta);
							if(result > alpha && result < beta)
								result = brd.search<mthd>(color,height - 1,alpha,beta);
						}else{
							result = brd.search<mthd>(color,height - 1,alpha,beta);
						}
					}else{
						result = brd.search<mthd>(color,height - 1,alpha,beta);
					}
					if(mthd & mthd_kill){
						ptr_val[pos] = result;
					}
					if(result <= alpha){
						return alpha;
					}
					if(result < beta){
						beta = result;
					}
					brd = *this;
					flag_flip = true;
				}
			}

			if(!flag_flip){
				calc_type num_diff = count(color) - count(!color);
				if(num_diff > 0){
					result =  num_diff + mark_max;
				}else if(num_diff < 0){
					result = num_diff - mark_max;
				}else{
					result = 0;
				}
				return result;
			}

			if(mthd & mthd_trans){
				auto& trans_interval = trans_ptr->second;
				if(beta < beta_save){
					trans_interval.second = beta;
				}
				if(beta > alpha_save){
					trans_interval.first = beta;
				}
			}

			return beta;
		}

		if(mthd & mthd_trans){
			auto& trans_interval = trans_ptr->second;
			if(alpha < beta_save){
				trans_interval.second = alpha;
			}
			if(alpha > alpha_save){
				trans_interval.first = alpha;
			}
		}

		return alpha;

	}

	#ifdef DEBUG_SEARCH
	};
	out << "<div color=" << color
		<< " height=" << height
		<< " alpha=" << alpha
		<< " beta=" << beta
		<< ">\n";
	do_print(out);
	calc_type result = fun();
	out << "result = " << result <<"\n"
		<< "</div>\n";
	return result;
	#endif
}

//Iterative_deepening(root)
//1:	firstguess <- 0
//2:	for depth = 1 to MAX_SEARCH_DEPTH do
//3:		firstguess <- MTDF(root, firstguess, depth)
//4:		if times_up() then
//5:		break
//6:	return firstguess

//if mthd & mthd_mtdf
//calc_type board::search_mtd(
//	cbool color,
//	cshort height,calc_type alpha,calc_type beta,
//	ccalc_type acc,cshort stage,calc_type gamma
//)const{
//	calc_type result = search_trans(color,height, gamma, gamma + 1, acc, stage);
//	if(result == gamma){
//		do{
//			--gamma;
//			result = search_trans(color,height, gamma, gamma + 1, acc, stage);
//		}while(result == gamma && result > alpha);
//	}else{
//		assert(result == gamma + 1);
//		do{
//			++gamma;
//			result = search_trans(color,height, gamma, gamma + 1, acc, stage);
//		}while(result == gamma + 1 && result < beta);
//	}
//	return result;
//}
