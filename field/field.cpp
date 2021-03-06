#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <utility>
#include <queue>
#include <set>
#include <map>
#include <deque>
#include <iomanip>
#include <cstdio>

using namespace std;
typedef  long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<VI> VVI;
#define  MP make_pair
#define  PB push_back
#define inf  1000000007
#define rep(i,n) for(int i=0;i<(int)(n);++i)

struct bot{
    int x;
    int y;
    int z;
    set<int> seed;
};

class field{
    int R,pointsize,sx,sy,sz,xlen,ylen,zlen;
    int bot_size = 20;
    ll cost=0;
    bool f[450][450][450]={};
    bool created[450][450][450]={};
    vector<string> trace;
    queue<string>bot_trace[20];
    vector<tuple<int,int,int> > points;
    vector<int> xpoint,ypoint,zpoint;
    bot robot[20];
    set<int> active_robot;
    public:
    void input(){
        scanf("%d",&R);
        scanf("%d",&pointsize);
        for(int i=0;i<pointsize;i++){
            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            f[a][b][c]=1;
            xpoint.push_back(a);
            ypoint.push_back(b);
            zpoint.push_back(c);
            points.push_back(make_tuple(a,b,c));
        }
        sort(xpoint.begin(), xpoint.end());
        xpoint.erase(unique(xpoint.begin(),xpoint.end()),xpoint.end());
        sort(ypoint.begin(), ypoint.end());
        ypoint.erase(unique(ypoint.begin(),ypoint.end()),ypoint.end());
        sort(zpoint.begin(), zpoint.end());
        zpoint.erase(unique(zpoint.begin(),zpoint.end()),zpoint.end());
        sx = xpoint[0];
        sy = ypoint[0];
        sz = zpoint[0];
        xlen = xpoint[xpoint.size()-1]-xpoint[0]+1;
        ylen = ypoint[ypoint.size()-1]-ypoint[0]+1;
        zlen = zpoint[zpoint.size()-1]-zpoint[0]+1;
    }
    string Flip(){
        return "Flip";
    }
    string Halt(){
        return "Halt";
    }
    string Wait(){
        return "Wait";
    }

    string move_str(int x,int y,int z){
        if(x==0&&y==0&&z==0){
            return "Wait";
        }
        if(x==0&&y==0){
            string s = to_string(z);
            return "Smove z "+ s;
        }
        if(y==0&&z==0){
            string s = to_string(x);
            return "Smove x "+ s;
        }
        if(x==0&&z==0){
            string s = to_string(y);
            return "Smove y "+ s;
        }
        if(x==0){
            string a = to_string(y);
            string b = to_string(z);
            return "Lmove y " + a + " z " + b;
        }
        if(y==0){
            string a = to_string(x);
            string b = to_string(z);
            return "Lmove x " + a + " z " + b;
        }
        if(z==0){
            string a = to_string(x);
            string b = to_string(y);
            return "Lmove x " + a + " y " + b;
        }
    }
    void move(int x,int y,int z,int bot_num){
        if(x==0&&y==0&&z==0)return;
        if(x==0&&y==0){
            if(z>15){
                bot_trace[bot_num].push(move_str(x,y,15));
                return move(x,y,z-15,bot_num);
            }else{
                bot_trace[bot_num].push(move_str(x,y,z));
                return;
            }
        }
        if(x==0&&z==0){
            if(y>15){
                bot_trace[bot_num].push(move_str(x,15,z));
                return move(x,y-15,z,bot_num);
            }else{
                bot_trace[bot_num].push(move_str(x,y,z));
                return;
            }
        }
        if(z==0&&y==0){
            if(x>15){
                bot_trace[bot_num].push(move_str(15,y,z));
                return move(x-15,y,z,bot_num);
            }else{
                bot_trace[bot_num].push(move_str(x,y,z));
                return;
            }
        }
        if(x>5){
            if(x<=15){
                bot_trace[bot_num].push(move_str(x,0,0));
                return move(0,y,z,bot_num);
            }else{
                bot_trace[bot_num].push(move_str(15,0,0));
                return move(x-15,y,z,bot_num);
            }
        }
        if(y>5){
            if(y<=15){
                bot_trace[bot_num].push(move_str(0,y,0));
                return move(x,0,z,bot_num);
            }else{
                bot_trace[bot_num].push(move_str(0,15,0));
                return move(x,y-15,z,bot_num);
            }
        }
        if(z>5){
            if(z<=15){
                bot_trace[bot_num].push(move_str(0,0,z));
                return move(x,y,0,bot_num);
            }else{
                bot_trace[bot_num].push(move_str(0,0,15));
                return move(x,y,z-15,bot_num);
            }
        }
        if(x>0&&y>0&&z>0){
            bot_trace[bot_num].push(move_str(0,0,z));
            return move(x,y,0,bot_num);
        }
        bot_trace[bot_num].push(move_str(x,y,z));
        return;
    }
    string fiss_str(int dx,int dy,int dz,int m){
        string a,b,c,d;
        a = to_string(dx);
        b = to_string(dy);
        c = to_string(dz);
        d = to_string(m);
        string ans = "Fission " + a + " " + b  + " " + c + " " + d;
        return ans;
    }
    void fiss(int dx,int dy,int dz,int m,int bot_num){
        bot_trace[bot_num].push(fiss_str(dx,dy,dz,m));
        int cnt =0;
        set<int> st;
        int new_robot;
        for(auto x:robot[bot_num].seed){
            if(cnt==0){
                active_robot.insert(x);
                st.insert(x);
                new_robot = x;
            }else{
                st.insert(x);
            }
            cnt++;
            if(cnt==m)break;
        }
        for(auto x:st){
            robot[bot_num].seed.erase(x);
            if(x!=new_robot){
                robot[new_robot].seed.insert(x);
            }
        }
        robot[new_robot].x = robot[bot_num].x+sx;
        robot[new_robot].y = robot[bot_num].y+sy;
        robot[new_robot].z = robot[bot_num].z+sz;
        
    }
    string fill_str(int dx,int dy,int dz){
        string a,b,c,d;
        a = to_string(dx);
        b = to_string(dy);
        c = to_string(dz);
        string ans = "Fill " + a + " " + b  + " " + c;
        return ans;
    }
    void fill(int dx,int dy,int dz,int bot_num){
        bot_trace[bot_num].push(fill_str(dx,dy,dz));
    }
    
    void fusion(int p,int s,int dx,int dy,int dz){
        string a,b,c,d,e,f;
        a = to_string(dx);
        b = to_string(dy);
        c = to_string(dz);
        d = to_string(-dx);
        e = to_string(-dy);
        f = to_string(-dz);
        bot_trace[p].push("FusionP "+a+" "+b+" "+c);
        bot_trace[s].push("FusionS "+d+" "+e+" "+f);
    }

    void firststep(){
        move(sx,sy,sz,0);
        while(!bot_trace[0].empty()){
            string tmp = bot_trace[0].front();
            bot_trace[0].pop();
            trace.push_back(tmp);
        }
        robot[0].x = sx;
        robot[0].y = sy;
        robot[0].z = sz;
        rep(i,19){
            robot[0].seed.insert(i+1);
        }
        active_robot.insert(0);
        return;
    }



    void show(){
        for(string s:trace){
            cout << s << endl;
        }
    }
};




int main(){
    field fd;
    fd.input();
    fd.firststep();
    fd.show();


    return 0;
}
