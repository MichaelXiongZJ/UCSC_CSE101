#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

void load_file(unordered_map<string, vector<string>> &movie_map, 
                unordered_map<string, vector<string>> &actor_map, 
                string filename){
    ifstream input;
    input.open(filename);
    string line, movieName, actorName;
    while(getline(input, line)){
        if(line.length() == 0){
            continue;
        }
        int spacePos = line.find(" ");
        movieName = line.substr(0, spacePos);
        line = line.substr(spacePos+1);
        movieName.append("||");
        if(movie_map.find(movieName) != movie_map.end()){   //if movie name duped
            int i = 0;
            do{
                i++;
                movieName.append(to_string(i));
            }while(movie_map.find(movieName) != movie_map.end());
        }
        movie_map[movieName];
        while(line.length()){
            int spacePos = line.find(" ");
            actorName = line.substr(0, spacePos);
            line = line.substr(spacePos+1);
            actor_map[actorName].push_back(movieName);
            movie_map[movieName].push_back(actorName);
        }
    }
}

string backTrace(string start, string dest, 
                unordered_map<string, string> &path_map){
    string path = dest;
    while(path_map[dest] != start){
        string temp = path_map[dest];
        dest = temp;
        if(temp.find("||") != string::npos){   //temp is a movie name
            int i = temp.find("||");
            temp = temp.substr(0, i);
            temp.insert(0, "-(");
            temp += ")-";
        }
        temp += " ";
        path.insert(0, temp);
    }
    start += " ";
    path.insert(0, start);
    return path;
}

string bfs(string start, string dest, 
            unordered_map<string, vector<string>> &movie_map, 
            unordered_map<string, vector<string>> &actor_map){
    unordered_map<string, string> path_map;
    queue<string> q;
    q.push(start);
    while(!q.empty()){
        string currActor = q.front();
        q.pop();
        if(currActor == dest){
            return backTrace(start, dest, path_map);
        }
        for(auto movieName: actor_map[currActor]){
            if(path_map.find(movieName) == path_map.end()){
                path_map[movieName] = currActor;
                for(auto actorName : movie_map[movieName]){
                    if(path_map.find(actorName) == path_map.end()){
                        q.push(actorName);
                        path_map[actorName] = movieName;
                    }
                }
            }
        }
    }
    return "Not present";
}

string getPath(string start, string dest, 
                unordered_map<string, vector<string>> &movie_map, 
                unordered_map<string, vector<string>> &actor_map){
    if(actor_map.find(start) == actor_map.end() || actor_map.find(dest) == actor_map.end()){
        return "Not present";
    }
    if(start == dest){
        return start;
    }
    return bfs(start, dest, movie_map, actor_map);
}

int main(int argc, char** argv){
    if (argc < 3){
        throw std :: invalid_argument("Usage: ./sixdegrees <INPUT FILE> <OUTPUT FILE>");
    }
    unordered_map<string, vector<string>> movie_map;
    unordered_map<string, vector<string>> actor_map;
    load_file(movie_map, actor_map, "cleaned_movielist.txt");
    ifstream input;
    ofstream output;
    input.open(argv[1]);
    output.open(argv[2]);
    string line, start, dest;
    while(getline(input, line)){
        if(line.length() == 0){
            continue;
        }
        if(line.back() == ' '){
            line.pop_back();    //remove whitespace at the end
        }
        int spacePos = line.find(" ");
        start = line.substr(0, spacePos);
        dest = line.substr(spacePos+1);
        output << getPath(start, dest, movie_map, actor_map) << endl;
    }
    input.close();
    output.close();
    return 0;
}