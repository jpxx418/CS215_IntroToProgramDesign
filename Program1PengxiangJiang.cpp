#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <iomanip>
#include <vector>

using namespace std;

bool getPlayer(int&, string&, string&, int&);
void getShooting(int&, int&, int&, int&, int&, int&);
void getRebounds(int&, int&);
void getOthers(int&, int&, int&, int&, int&);
void findTopOffensivePlayer(vector<int>&, vector<string>&, vector<double>&);
void findTopDefensivePlayer(vector<int>&, vector<string>&, vector<double>&);
void findMostValuablePlayer(vector<int>&, vector<string>&, vector<double>&);

ifstream infile;

int main(int argc, char** argv)
{  
int uniform_number, minutes; string first_name, last_name;
int field_goal_attempts, field_goals_made, three_point_attempts, three_pointers_made, free_throw_attempts, free_throw_made;
int offensive_rebounds, defensive_rebounds;
int steals, blocked_shots, assists, turnovers, personal_fouls;
double field_goal, three_point, free_throw, points_per_48; int totals_rebounds, points;
int total_min = 0, total_fga = 0, total_fgm = 0, total_3pa = 0, total_3pm = 0; double total_pct1, total_pct2, total_pct3, total_p48;
int total_fta = 0, total_ftm = 0, total_off = 0, total_def = 0, total_tot = 0, total_stl = 0;
int total_blk = 0, total_ast = 0, total_to = 0, total_pf = 0, total_pts = 0;

vector <int> player_number;
vector <string> player_name;
vector <double> offensive_rate;
vector <double> defensive_rate;
vector <double> mvp_rate;

double offensiverate, defensiverate, mvprate;

cout << "Player Name           Min   FGA  FGM   PCT  3PA  3PM   PCT  FTA  FTM   PCT  OFF  DEF  TOT  STL  BLK  AST   TO  PF  PTS  P48" << endl;

while (getPlayer(uniform_number, first_name, last_name, minutes))
{
getShooting(field_goal_attempts, field_goals_made, three_point_attempts, three_pointers_made, free_throw_attempts, free_throw_made );
getRebounds(offensive_rebounds, defensive_rebounds);
getOthers(steals, blocked_shots, assists, turnovers, personal_fouls);

if ( field_goal_attempts == 0)
    {
       field_goal = 0;
    }
else 
    {
       field_goal = (field_goals_made + 0.0) / (field_goal_attempts + 0.0);
    }
if ( three_point_attempts == 0) 
    {  
       three_point = 0;
    }
else 
    { 
       three_point = (three_pointers_made + 0.0) / (three_point_attempts + 0.0);
    }
if ( three_point_attempts == 0)
    { 
       free_throw = 0;
    }
else 
    {
       free_throw = (free_throw_made + 0.0) / (free_throw_attempts + 0.0);
    }
totals_rebounds = offensive_rebounds + defensive_rebounds;
points = 2 * field_goals_made + three_pointers_made + free_throw_made;
points_per_48 = points / (minutes / 48.0);

total_min = total_min + minutes; 
total_fga = total_fga + field_goal_attempts;
total_fgm = total_fgm + field_goals_made; 
total_3pa = total_3pa + three_point_attempts;
total_3pm = total_3pm + three_pointers_made; 
total_fta = total_fta + free_throw_attempts;
total_ftm = total_ftm + free_throw_made; 
total_off = total_off + offensive_rebounds;
total_def = total_def + defensive_rebounds; 
total_tot = total_tot + totals_rebounds;
total_stl = total_stl + steals; 
total_blk = total_blk + blocked_shots; 
total_ast = total_ast + assists;
total_to = total_to + turnovers; 
total_pf = total_pf + personal_fouls; 
total_pts = total_pts + points;
total_p48 = total_p48 + points_per_48;

string full_name = last_name + ", " + first_name;

if ( three_point == 0)
   { 
     cout << left << setw(21) << full_name << " " << right << setw(3) << minutes << setw(6) << field_goal_attempts <<
     setw(5) << field_goals_made << fixed << setprecision(3) << setw(6) << field_goal << setw(5) << three_point_attempts <<
     setw(5) << three_pointers_made << setw(6) << "---" << setw(5) << free_throw_attempts << setw(5) << free_throw_made <<
     setw(6) << free_throw << setw(5) << offensive_rebounds << setw(5) << defensive_rebounds << setw(5) << totals_rebounds <<
     setw(5) << steals << setw(5) << blocked_shots << setw(5) << assists << setw(5) << turnovers <<
     setw(4) << personal_fouls << setw(5) << points << fixed << setprecision(1) << setw(5) << points_per_48 << endl;
   }
else
   { 
     cout << left << setw(21) << full_name << " " << right << setw(3) << minutes << setw(6) << field_goal_attempts <<
     setw(5) << field_goals_made << fixed << setprecision(3) << setw(6) << field_goal << setw(5) << three_point_attempts <<
     setw(5) << three_pointers_made << setw(6) << three_point << setw(5) << free_throw_attempts << setw(5) << free_throw_made <<
     setw(6) << free_throw << setw(5) << offensive_rebounds << setw(5) << defensive_rebounds << setw(5) << totals_rebounds <<
     setw(5) << steals << setw(5) << blocked_shots << setw(5) << assists << setw(5) << turnovers << setw(4) << personal_fouls <<
     setw(5) << points << fixed << setprecision(1) << setw(5) << points_per_48 << endl;
   }

offensiverate = points_per_48 + (offensive_rebounds/ (minutes / 48.0)) * 0.4 + (assists / (minutes / 48)) * 0.4 - (turnovers / (minutes / 48)) *0.4;
defensiverate = (defensive_rebounds / (minutes / 48)) * 0.4 + (blocked_shots / (minutes / 48)) * 0.4 + (steals / (minutes / 48)) * 0.4 - (personal_fouls / (minutes / 48));
mvprate = defensiverate * 0.67 + offensiverate * 0.33;
player_number.push_back(uniform_number);
player_name.push_back(first_name + " " + last_name);
offensive_rate.push_back(offensiverate);
defensive_rate.push_back(defensiverate);
mvp_rate.push_back(mvprate);
}

total_pct1 = (total_fgm + 0.0) / total_fga;
total_pct2 = (total_3pm + 0.0)/ total_3pa;
total_pct3 = (total_ftm + 0.0) / total_fta; total_p48 = total_pts / (total_min / 48.0);

cout << left << setw(21) << "TOTAL" <<  right << setw(3) << total_min << setw(6) << total_fga <<
        setw(5) << total_fgm << fixed << setprecision(3) << setw(6) << total_pct1 << setw(5) << total_3pa <<
        setw(5) << total_3pm << setw(6) << total_pct2 << setw(5) << total_fta << setw(5) << total_ftm <<
        setw(6) << total_pct3 << setw(5) << total_off << setw(5) << total_def << setw(5) << total_tot <<
        setw(5) << total_stl << setw(5) << total_blk << setw(5) << total_ast << setw(5) << total_to <<
        setw(4) << total_pf << setw(5) << total_pts << fixed << setprecision(1) << setw(5) << total_p48 << endl;
cout << endl;

findTopOffensivePlayer(player_number, player_name, offensive_rate);
findTopDefensivePlayer(player_number, player_name, defensive_rate);
findMostValuablePlayer(player_number, player_name, mvp_rate);
return 0;
}

void findTopOffensivePlayer(vector<int>& player_number, vector<string>& player_name, vector<double>& offensive_rate)
{  
    int n; double m = 0;
   for (int i = 0; i < offensive_rate.size(); i++)
   { while (offensive_rate[i] > m)
     { 
       m = offensive_rate[i];
       n = i;
     }
   }
cout << "Top Offensive Player:" << endl;
cout << player_number[n] << " " << player_name[n] << endl;
cout << endl;
return;
}

void findTopDefensivePlayer(vector<int>& player_number, vector<string>& player_name, vector<double>& defensive_rate)
{  
    int n; double m = 0;
   for (int i = 0; i < defensive_rate.size(); i++)
   { while (defensive_rate[i] > m)
     { 
       m = defensive_rate[i];
       n = i;
     }
   }
cout << "Top Defensive Player:" << endl;
cout << player_number[n] << " " << player_name[n] << endl;
cout << endl;
return;
}

void findMostValuablePlayer(vector<int>& player_number, vector<string>& player_name, vector<double>& mvp_rate)
{
    int n; double m = 0;
   for (int i = 0; i < mvp_rate.size(); i++)
   { while (mvp_rate[i] > m)
     { 
       m = mvp_rate[i];
       n = i;
     }
   }
cout << "Most Valuable Player:" << endl;
cout << player_number[n] << " " << player_name[n] << endl;
return;
}

bool getPlayer(int& num, string& first, string& last, int& min)
{  if(!infile.is_open())
   {  infile.open("lab3.dat");
   }
   infile >> num;
   if(infile.eof())
   {  infile.close();
      return false;
   }
   else
   {  assert(!infile.fail());
   }
   infile >> first;
   assert(!infile.fail());
   infile >> last;
   assert(!infile.fail());
   infile >> min;
   assert(!infile.fail());
   return true;
}

void getShooting(int& fga, int& fgm, int& tpa, int& tpm, int& fta, int& ftm)
{  infile >> fga;
   assert(!infile.fail());
   infile >> fgm;
   assert(!infile.fail());
   infile >> tpa;
   assert(!infile.fail());
   infile >> tpm;
   assert(!infile.fail());
   infile >> fta;
   assert(!infile.fail());
   infile >> ftm;
   assert(!infile.fail());
   return;
}

void getRebounds(int& off, int& def)
{  infile >> off;
   assert(!infile.fail());
   infile >> def;
   assert(!infile.fail());
   return;
}

void getOthers(int& stl, int& blk, int& ast, int& to, int& pf)
{  infile >> stl;
   assert(!infile.fail());
   infile >> blk;
   assert(!infile.fail());
   infile >> ast;
   assert(!infile.fail());
   infile >> to;
   assert(!infile.fail());
   infile >> pf;
   assert(!infile.fail());
   return;
}



