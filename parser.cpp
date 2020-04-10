#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cassert>
#include <tuple>

using namespace std;

template<typename...Args>
class CSVParser{
private:
    vector<tuple<Args...>> Tupler;
        tuple<Args...> Tuple1;
        ifstream& file;
        int n;
        char delimiter;
        char mark;
        string dump;
        vector<string> row;



public:

    CSVParser(){
    };
    CSVParser(ifstream& F,int N):
        delimiter(','),
         mark('"'),
         file(F),
         n(N)
    {
        for (unsigned int i = 0; i < n; i++) {
                getline(file,dump);
        }

    }
    ~CSVParser(){
    file.close();

    }

    void CRT(){
    }

    vector<string> ParseRow(ifstream& file){
    unsigned int NumOfQuotes = 0;
    stringstream stream;
    unsigned int i=0;
    while (!file.eof()) {

    char Char=file.get();
    i++;

    if ((Char==mark) and (NumOfQuotes%2==0))
        {
        stream<<Char;
        NumOfQuotes++;

        }

    else if (Char==mark)
    {
        stream<<mark;
        NumOfQuotes++;

    }

    else if ((Char==mark) and (NumOfQuotes%2==1)){
            string err="Error at line  at  symbol";
              throw runtime_error(err );
             }
    else if ((Char==delimiter) and (NumOfQuotes%2==0))
    {
        row.push_back(stream.str());
        stream.str("");//

    }
    else if (Char=='\n')
    {
        row.push_back(stream.str());
        stream.str("");//

    }
        else if (Char!=-1)
            stream<<Char;

    }

    row.push_back(stream.str());
return row;


    }
void Parse(){
        row = ParseRow(file);
        cout<<sizeof...(Args);

       ParseArg(make_index_sequence<sizeof...(Args)> {});
    //function<0>(get<0>(Tuple1));
       //cout<<get<0>(Tuple1)<<endl;

        //    get<1>(Tuple1)=function<1>(get<1>(Tuple1));
        //cout<<get<1>(Tuple1)<<endl;


    }
template <size_t... Is>
void ParseArg(index_sequence<Is...> sequence) {
       // ((ParseArgum(get<Is>(Tuple1), Is)),...);
       // (ParseArgum(get<Is>(Tuple1)..., Is...));
    }

template <typename T>
    void ParseArgum(T& tuple_element, size_t num) {
        function<num>(tuple_element);
    }

void something_else(Args... values) {
		const int a[] = {(std::cout << values << ' ', 0)...};
		static_cast<void>(a);
    }


    template <int i,class T>
    auto function(T& tup) {
        stringstream k;
        T gg;
        k<<row[i];
        k>>gg;
        get<i>(Tuple1)=gg;
    }




void view(){
    vector<string>::iterator it1;
    string st="asd";
    int g=5;
    cout<<sizeof(st)<<endl;
    cout<<sizeof(g)<<endl;
for(it1 = row1.begin(); it1 != row1.end(); it1++)
{
cout << *it1<<sizeof(*it1)<<endl ;
}
}
};



int main(){

ifstream file("test1.txt");

CSVParser<int, string> parser(file, 0);
parser.Parse();


}


