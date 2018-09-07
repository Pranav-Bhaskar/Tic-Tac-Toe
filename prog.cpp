#include<iostream>

using namespace std;

int box[3][3] = {};
/* 0 - by default
 * 1 - by user
 * 4 - by comp
*/
int stp_i;
int stp_j;
int pos;
int moves[5];
int mover = 0;
int doves[5];
int dover = 0;
void head(){
	cout<<"  +================================================================================================================================================+"<<endl;
	cout<<"  |---------------------------------------------------------A Tic-Tac-Toe based on C++-------------------------------------------------------------|"<<endl;
	cout<<"  +================================================================================================================================================+"<<endl;
}
void disp(){
	system("clear");
	head();
	cout<<"\n\t\t\t\t\t||==============||==============||==============||";
	for(int i=0;i<3;++i){
		cout<<endl<<endl<<"\t\t\t\t\t||";
		for(int j=0;j<3;++j){
			cout<<"\t";
			if(box[i][j] == 0)
				cout<<"-";
			if(box[i][j] == 1)
				cout<<"X";
			if(box[i][j] == 4)
				cout<<"O";
			cout<<"\t||";
		}
		cout<<"\n\n\t\t\t\t\t||==============||==============||==============||";
	}
	cout<<endl<<endl<<endl;
}

int killer(){
	for(int i=0;i<3;++i)
		for(int j=0;j<3;++j)
			if(box[i][j] == 0)
				return 0;
	return 1;
}

int row(int box[3][3]){
	int t = 0;
	for(int i=0;i<3;++i){
		t = 0;
		for(int j=0;j<3;++j){
			t += box[i][j];
		}
		if(t == 3 || t == 12){
			return t;
		}
	}
	return 0;
}

int col(int box[3][3]){
	int t = 0;
	for(int i=0;i<3;++i){
		t = 0;
		for(int j=0;j<3;++j){
			t += box[j][i];
		}
		if(t == 3 || t == 12){
			return t;
		}
	}
	return 0;
}

int dig(int box[3][3]){
	int t = 0;
	for(int i=0;i<3;++i){
		t += box[i][i];
	}
	if(t == 3 || t == 12){
		return t;
	}
	t = box[0][2] + box[1][1] + box[2][0];
	if(t == 3 || t == 12){
		return t;
	}
	return 0;
}

int check(int b[3][3] = box){
	int t = row(b) + col(b) + dig(b);
	return t;
}

int is_cent(int mov){
	if(mov == 4)
		return 1;
	return 0;
}

int is_cor(int mov){
	if((mov == 0)||(mov == 2)||(mov == 6)||(mov == 8))
		return 1;
	return 0;
}

int is_edg(int mov){
	if((mov == 1)||(mov == 3)||(mov == 5)||(mov == 7))
		return 1;
	return 0;
}

int cal_val(int mov){
	return box[mov/3][mov%3];
}

int cal_opp(int mov){
	return 8 - mov;
}

int mrk_mov(int mov, int val){
	if(box[mov/3][mov%3]){
		cout<<"\nERROR : Over Writing on space";
		return 0;
	}
	box[mov/3][mov%3] = val;
	if(val == 4)
		doves[dover++] = mov;
	return 1;
}

int mrk_cent(){
	return mrk_mov(4, 4);
}

int mrk_opp(){
	return mrk_mov(cal_opp(pos), 4);
}

int mrk_cor(){
	for(int i=0;i<9;++i){
		if(is_cor(i)){
			if(cal_val(i) == 0){
				mrk_mov(i, 4);
				return 1;
			}
		}
	}
	return 0;
}

int mrk_edg(){
	for(int i=0;i<9;++i){
		if(is_edg(i)){
			if(cal_val(i) == 0){
				mrk_mov(i, 4);
				return 1;
			}
		}
	}
	return 0;
}

int mrk_btw(int pos1){
		return mrk_mov((pos1 + pos) - 4, 4);
}

void set(){
	cout<<"\n\n\n";
	do{
		do{
			cout<<"\nEnter Row : ";
			cin>>stp_i;
			if(cin.fail()){
				cout<<"Try Entering Integer Values for a change";
				stp_i = 69;
				cin.clear();
				cin.ignore(999,'\n');
			}
		}while((stp_i<0)||(stp_i>2)); 
		
		do{
			cout<<"\nEnter Col : ";
			cin>>stp_j;
			if(cin.fail()){
				cout<<"Try Entering Integer Values for a change";
				stp_j = 69;
				cin.clear();
				cin.ignore(999,'\n');
			}
		}while((stp_j<0)||(stp_j>2));
		
		pos = (stp_i*3)+stp_j;
		
	}while(!mrk_mov(pos, 1));
	moves[mover++] = pos;
}

int make(){
	int tmp[3][3] = {};
	for(int i=0;i<9;++i){
		if(cal_val(i) == 0){
			for(int j=0;j<3;++j){
				for(int k=0;k<3;++k){
					tmp[j][k] = box[j][k];
				}
			}
			tmp[i/3][i%3] = 4;
			if(check(tmp)){
				mrk_mov(i, 4);
				return 1;
			}
		}
	}
	return 0;
}

int stop(){
	int tmp[3][3] = {};
	for(int i=0;i<9;++i){
		if(cal_val(i) == 0){
			for(int j=0;j<3;++j){
				for(int k=0;k<3;++k){
					tmp[j][k] = box[j][k];
				}
			}
			tmp[i/3][i%3] = 1;
			if(check(tmp)){
				mrk_mov(i, 4);
				return 1;
			}
		}
	}
	return 0;
}

int best_move(){
	if(!make()){
		if(!stop()){
			return 0;
		}
	}
	return 1;
}

void rand_move(){
	for(int i=0;i<9;++i){
		if(cal_val(i) == 0){
			mrk_mov(i, 4);
			return ;
		}
	}
	cout<<"\nERROR : Couldnt make a rand move";
}

void loop(){
	while(1){
		if(check(box) >= 12){
			cout<<"\nComp Wins";
			return ;
		}
		if(check(box) > 0){
			cout<<"\nPlayer Wins : It Would Be Realy Kind Of You If You Could Send It To MaDaR4 :-\n";
			for(int i=0;i<mover;++i)
				cout<<moves[i]<<",";
			cout<<";";
			for(int i=0;i<dover;++i)
				cout<<doves[i]<<",";
			return ;
		}
		set();
		if(check(box) >= 12){
			cout<<"\nComp Wins";
			return ;
		}
		if(check(box) > 0){
			cout<<"\nPlayer Wins : It Would Be Realy Kind Of You If You Could Send It To MaDaR4 :-\n";
			for(int i=0;i<mover;++i)
				cout<<moves[i]<<",";
			cout<<";";
			for(int i=0;i<dover;++i)
				cout<<doves[i]<<",";
			return ;
		}
		if(killer())
			return ;
		if(!best_move()){
			rand_move();
		}
		disp();
	}
}

void cor1(){
	set();
	if(pos == cal_opp(moves[mover - 2])){
		if(!mrk_edg()){
			cout<<"\nERROR : not able to set a edge in cor1";
		}
	}
	else
	if(!best_move()){
		if(!mrk_cor()){
			cout<<"\nERROR : not able to set a corner in cor1";
		}
	}
	disp();
	loop();
}

void cse_cor(){
	mrk_cent();
	disp();
	cor1();
}

void cent1(){
	set();
	if(pos == cal_opp(doves[dover - 1])){
		if(!mrk_cor())
			cout<<"\nERROR : At cent1 tried to mark cor";
	}
	else{
		stop();
	}
	disp();
	loop();
}

void cse_cent(){
	mrk_cor();
	disp();
	cent1();
}

void edg1(){
	set();
	if((pos != cal_opp(moves[mover - 2]))&&(is_edg(pos))){
		if(!mrk_btw(moves[mover - 2])){
			cout<<"\nERROR : Could'nt Mark Between In edg1";
		}
	}
	else{
		if(!best_move()){
			rand_move();
		}
	}
	disp();
	loop();
}

void cse_edg(){
	mrk_cent();
	disp();
	edg1();
}

void begin(){
	set();
	if(is_cor(pos)){
		cse_cor();
		return ;
	}
	if(is_cent(pos)){
		cse_cent();
		return ;
	}
	if(is_edg(pos)){
		cse_edg();
		return ;
	}
	else{
		cout<<"\nERROR 1 : Error in the begining";
	}
}

int main ()
{
	disp();
	cout<<"\nBEWARE 1. YOU ARE 'X'"<<"\n       2. Here 0 indexing system is followed";
	begin();
	cout<<"\nEnd Of The Game\n\n\n\n\n";
	return 0;
}
