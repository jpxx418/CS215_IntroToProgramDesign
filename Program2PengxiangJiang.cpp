#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include<iomanip>
#include <fstream>

using namespace std;

struct Player
{
    int num;
    string first;
    string last;
    int min;
    int fga;
    int fgm;
    double fg;
    int tpa;
    int tpm;
    double tp;
    int fta;
    int ftm;
    double ft;
    int off;
    int def;
    int Total_rebounds;
    int stl;
    int blk;
    int ast;
    int to;
    int pf;
    double Points_Per_48;
    double Offensive_Rating;
    double Defensive_Rating;
    double MVP_Rating;
};

bool getPlayerStats(Player*);
void calcPercentages(Player*);
void findTopOffensivePlayer(vector<Player*>);
void findTopDefensivePlayer(vector<Player*>);
void findMostValuablePlayer(vector<Player*>);
void outputPlayers(vector<Player*>);
void deallocatePointers(vector<Player*>);

ifstream infile;

int main(int argc, char** argv) 
{
     cout << "Player Name           Min   FGA  FGM   PCT  3PA  3PM   PCT  FTA  FTM   PCT  OFF  DEF  TOT  STL  BLK  AST   TO  PF  PTS  P48" << endl;
     vector < Player*> players;
     Player* data = new Player;
     while(getPlayerStats(data))
     {
       calcPercentages(data);
       players.push_back(data);
       data = new Player;
     }
     
     for( int i =0; i < players.size(); i++)
     {
         players[i]->Offensive_Rating = players[i]->Points_Per_48 + 0.4 * static_cast<double>(players[i]->off) / (players[i]->min / 48.0) + 0.4 * static_cast<double>(players[i]->ast) / (players[i]->min / 48.0) - 0.4 * static_cast<double>(players[i]->to) / (players[i]->min / 48.0);
         players[i]->Defensive_Rating = 0.4 * static_cast<double>(players[i]->def) / (players[i]->min / 48.0) + 0.4 * static_cast<double>(players[i]->blk) / (players[i]->min / 48.0) + 0.4 * static_cast<double>(players[i]->stl) / (players[i]->min / 48.0) - static_cast<double>(players[i]->pf) / (players[i]->min / 48.0);
         players[i]->MVP_Rating = (players[i]->Defensive_Rating * 0.67) + (players[i]->Offensive_Rating * 0.33);
     }
     
    outputPlayers(players);
    findTopOffensivePlayer(players);
    findTopDefensivePlayer(players);
    findMostValuablePlayer(players);
    deallocatePointers(players);

    return 0;
}


bool getPlayerStats(Player* data)
{
  if(!infile.is_open())
    {
        infile.open("lab3.dat");
    }

    infile >> data->num;

    if(infile.eof())
    {
        infile.close();
        return false;
    } else
    {
        assert(!infile.fail());
    }

    infile >> data->first;
    assert(!infile.fail());

    infile >> data->last;
    assert(!infile.fail());

    infile >> data->min;
    assert(!infile.fail());

    infile >> data->fga;
    assert(!infile.fail());

    infile >> data->fgm;
    assert(!infile.fail());

    infile >> data->tpa;
    assert(!infile.fail());

    infile >> data->tpm;
    assert(!infile.fail());

    infile >> data->fta;
    assert(!infile.fail());

    infile >> data->ftm;
    assert(!infile.fail());

    infile >> data->off;
    assert(!infile.fail());

    infile >> data->def;
    assert(!infile.fail());

    infile >> data->stl;
    assert(!infile.fail());

    infile >> data->blk;
    assert(!infile.fail());

    infile >> data->ast;
    assert(!infile.fail());

    infile >> data->to;
    assert(!infile.fail());

    infile >> data->pf;
    assert(!infile.fail());

    return true;
}


void calcPercentages(Player* data)
{
    data->fg = static_cast<double>(data->fgm) / static_cast<double>(data->fga);
    data->tp = static_cast<double>(data->tpm) / static_cast<double>(data->tpa);
    data->ft = static_cast<double>(data->ftm) / static_cast<double>(data->fta);
    data->Total_rebounds = data->off + data->def;
    int points = 2 * data->fgm + data->tpm + data->ftm;
    data->Points_Per_48 =  static_cast<double>(points)/(data->min/48.0);
    return;
}


void findTopOffensivePlayer(vector<Player*> players)
{
   int m;
   double n=0;
   for( int i =0; i < players.size(); i++)
    {
         if( players[i]->Offensive_Rating > n)
           {
              n = players[i]->Offensive_Rating;
              m = i;
           }
     }
     cout << "Top Offensive Player:" << endl ;
     cout <<  players[m]->num << " " << players[m]->first<< " " <<players[m]->last << endl;
     return;
}


void findTopDefensivePlayer(vector<Player*> players)
{
   int m;
   double n=0;
   for( int i =0; i < players.size(); i++)
    {
         if( players[i]->Defensive_Rating > n)
        {
              n = players[i]->Defensive_Rating;
              m = i;
         }
     }
     cout << "Top Defensive Player:" << endl ;
     cout <<  players[m]->num << " " << players[m]->first << " " << players[m]->last << endl;
     return;
}


void findMostValuablePlayer(vector<Player*> players)
{
   int m;
   double n;
   for( int i =0; i < players.size(); i++)
    {
         if ( players[i]->MVP_Rating > n)
         {
              n = players[i]->MVP_Rating;
              m = i;
         }
     }
     cout << "Most Value Player:" << endl ;
     cout << players[m]->num << " " << players[m]->first << " " << players[m]->last << endl;
     return;
}


void outputPlayers(vector< Player*> players)
{
    double total_p48=0;
    int total_min = 0,total_fga = 0,total_fgm = 0,total_tpa = 0,total_tpm = 0,total_fta = 0,total_ftm = 0,total_off = 0,total_def = 0,total_stl = 0,total_blk = 0,total_ast = 0,total_to = 0,total_pf = 0,total_tot = 0,total_pts = 0;
    for(int i = 0; i < players.size(); i++)
    {
        total_min = total_min + players[i]->min;
        total_fga = total_fga + players[i]->fga;
        total_fgm = total_fgm + players[i]->fgm;
        total_tpa = total_tpa + players[i]->tpa;
        total_tpm = total_tpm + players[i]->tpm;
        total_fta = total_fta + players[i]->fta;
        total_ftm = total_ftm + players[i]->ftm;
        total_off = total_off + players[i]->off;
        total_def = total_def + players[i]->def;
        total_stl = total_stl + players[i]->stl;
        total_blk = total_blk + players[i]->blk;
        total_ast = total_ast + players[i]->ast;
        total_to = total_to + players[i]->to;
        total_pf = total_pf + players[i]->pf;
        total_tot = total_tot + (players[i]->off+ players[i]->def);
        int points = 2 * players[i]->fgm+ players[i]->tpm+ players[i]->ftm;
        total_pts = total_pts + points;
        total_p48 = static_cast<double>(total_pts) / (total_min / 48.0);
        
    string full_name = players[i]->last + ", " + players[i]->first;
        
    cout << left << setw(21) << full_name << " " << right << setw(3) << players[i]->min << setw(6) << players[i]->fga<< setw(5) << players[i]-> fgm; 
    
     if(players[i]->fga == 0)
        {
            cout << "---";
        }
     else
        {
            players[i]->fg = static_cast<double>( players[i]->fgm) / static_cast<double>( players[i]->fga);
            cout << fixed << setprecision(3) << setw(6) << players[i]->fg;
        }
    
    cout << setw(5) << players[i]-> tpa <<setw(5) << players[i]->tpm;
    
    if(players[i]->tpa == 0)
        {
            cout << setw(6) << "---";
        }
    else
        {
            players[i]->tp = static_cast<double>( players[i]->tpm)/static_cast<double>( players[i]->tpa);
            cout << setw(6) << players[i]->tp;
        }
    
    cout << setw(5) << players[i]-> fta<<setw(5) << players[i]-> ftm; 
              
    if(players[i]->fta == 0)
        {
            cout << setw(6) << "---";
        }
    else
        {
            players[i]->ft = static_cast<double>( players[i]->ftm)/static_cast<double>( players[i]->fta);
            cout << setw(6) << players[i]->ft;
        }        
    
    
    cout << setw(5) << players[i]->off << setw(5) << players[i]->def << setw(5) << players[i]->off+ players[i]->def << setw(5) <<  players[i]->stl << setw(5) <<  players[i]->blk << setw(5) <<  players[i]->ast 
         << setw(5) << players[i]->to << setw(4) << players[i]->pf << setw(5) << 2* players[i]->fgm+ players[i]->tpm+ players[i]->ftm << fixed << setprecision(1) << setw(5) << static_cast<double>(2* players[i]->fgm+ players[i]->tpm+ players[i]->ftm)/( players[i]->min / 48.0) 
         << endl;
         
    }
    
    cout << left << setw(21) << "TOTAL" << right << setw(3) << total_min << setw(6) << total_fga << setw(5) << total_fgm << setw(6) << fixed << setprecision(3) << static_cast<double>(total_fgm)/static_cast<double>(total_fga) << setw(5) << total_tpa
         << setw(5) << total_tpm << setw(6) <<  static_cast<double>(total_tpm)/static_cast<double>(total_tpa) << setw(5) << total_fta << setw(5) << total_ftm
         << setw(6) << static_cast<double>(total_ftm)/static_cast<double>(total_fta) << setw(5) << total_off << setw(5) << total_def
         << setw(5) << total_tot << setw(5) << total_stl << setw(5) << total_blk << setw(5) << total_ast << setw(5) << total_to << setw(4) <<total_pf << setw(5) <<total_pts << fixed << setprecision(1) << setw(5) << total_p48 <<endl;
    
    return;
}


void deallocatePointers(vector<Player*> players)
{
    for(int i = 0; i < players.size(); i ++)
    {
       delete players[i];
    }
    return;
}







