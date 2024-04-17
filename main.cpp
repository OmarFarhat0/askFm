#include<iostream>
#include<fstream>
#include <vector>

using namespace std;

fstream file("file.txt", ios::in | ios::out | ios::app);

struct question {
    int id, from, to;
    string content;
    vector<string> answer;

    void printQuestion() {
        cout << "ID question: " << id << " to user ID : " << to << endl;
        cout << "question: " << content << endl;
        for (int j = 0; j < answer.size(); j++) {
            cout << "answer: " << answer[j] << endl;
        }
    }

    void addAnswer(string add) {
        answer.push_back(add);
    }

    void deleteQuestion(int idQuDelete) {
        id = -1;
    }

    void printQuFromFile() {
        file << id << " " << from << " " << to << " " << content << " " << answer.size() << endl;
        for (int i = 0; i < answer.size(); i++) {
            file << answer[i] << " ";
        }
        cout << endl;
    }

    void readQuFromFile(int numberOfAnswerThisQuesiton) {
        file >> id >> from >> to >> content;
        for (int i = 0; i < numberOfAnswerThisQuesiton; i++) {
            file >> answer[i];
        }
    }
};

struct user {
    int id;
    string name, userName, email, password;
    vector<question> quFromMe, quToMe;

    void read(int a) {
        cout << "Enter your name plz" << endl;
        cin >> name;

        cout << "Enter your user name plz" << endl;
        cin >> userName;

        cout << "Enter your email plz" << endl;
        cin >> email;

        cout << "Enter your password plz" << endl;
        cin >> password;

        id = a;
    }

    void readUserFromFile(int aidId) {
        file >> id >> name >> userName >> email >> password;
    }

    void printUserFromFile() {
        file << id << " " << name << " " << userName << " " << email << " " << password << endl;
    }

    void printUser() {
        cout << "id : " << id << "          name : " << name << endl;
    }

    void printFromMe() {
        if (!quFromMe.size()) cout << "There are no questions" << endl;
        for (int i = 0; i < quFromMe.size(); i++) {
            if (quFromMe[i].id == -1) {
                continue;
            }
            quFromMe[i].printQuestion();
        }
    }

    void printToMe() {
        if (!quToMe.size()) cout << "There are no questions" << endl;
        for (int i = 0; i < quToMe.size(); i++) {
            if (quToMe[i].id == -1) {
                continue;
            }
            cout << "ID: " << quToMe[i].id << " to user ID : " << quToMe[i].to << endl;
            cout << "question: " << quToMe[i].content << endl;
            for (int j = 0; j < quToMe[i].answer.size(); j++) {
                cout << "answer: " << quToMe[i].answer[j] << endl;
            }
        }
    }

    void addQuFromMe(question a) {
        quFromMe.push_back(a);
    }

    void addQuToMe(question a) {
        quToMe.push_back(a);
    }
};

struct system {
    vector<user> allUsers;
    user userNow;
    int numberOfUsers = 0, numberOfQu = 0, numberOfAnswer = 0;

    /*system() { //READ FROM FILE
        file >> numberOfUsers >> numberOfQu >> numberOfAnswer;

        for (int i = 0; i < numberOfUsers; i++) {
            user add;
            add.readUserFromFile(i+1);
            allUsers.push_back(add);
        }

        for (int i = 0; i < numberOfQu; i++) {
            question add;
            int numberOfAnswerThisQuesiton;
            file >> numberOfAnswerThisQuesiton;
            add.readQuFromFile(numberOfAnswerThisQuesiton);

            allUsers[add.from-1].addQuFromMe(add);
            allUsers[add.to-1].addQuToMe(add);
        }
    }

    ~system() { //DELETE ALL DATA AND OVERWRITE IT

        //DELETE

        //OVERWRITE

        file.close();

        file.open("file.txt", ios::out);

        file << numberOfUsers << " " << numberOfQu << " " << numberOfAnswer << endl;

        for (int i = 0; i < allUsers.size(); i++) {
            allUsers[i].printUserFromFile();
        }

        bool visited[1000] = {0}; //visited question by id
        for (int i = 0; i < allUsers.size(); i++) {

            for (int j = 0; j < allUsers[i].quFromMe.size(); j++) {
                if (!visited[allUsers[i].quFromMe[j].id]) {
                    allUsers[i].quFromMe[j].printQuFromFile();
                    visited[allUsers[i].quFromMe[j].id] = true;
                }
            }
            for (int j = 0; j < allUsers[i].quToMe.size(); j++) {
                if (!visited[allUsers[i].quToMe[j].id]) {
                    allUsers[i].quToMe[j].printQuFromFile();
                    visited[allUsers[i].quToMe[j].id] = true;
                }
            }
        }
    }*/

    void systemSignUp() {
        numberOfUsers++;
        user add;
        add.read(numberOfUsers);
        allUsers.push_back(add);
    }

    void systemLogin() {
        cout << "Enter your user name plz" << endl;
        cin >> userNow.userName;

        cout << "Enter your password plz" << endl;
        cin >> userNow.password;

        for (int i = 0; i < allUsers.size(); i++) {
            if (allUsers[i].userName==userNow.userName && allUsers[i].password==userNow.password) {
                userNow.id = i+1;
            }
        }
    }

    void systemPrintFromMe(){
        allUsers[userNow.id-1].printFromMe();
    }

    void systemPrintTomMe(){
        allUsers[userNow.id-1].printToMe();
    }

    void systemPrintAllUsers() {
        if (!allUsers.size()) cout << "There are no users" << endl;
        for (int i = 0; i < allUsers.size(); i++) {
            allUsers[i].printUser();
        }
    }

    void systemDeleteQu() {
        cout << "Please enter the ID of the message to be deleted" << endl;
        int idQuDelete;
        cin >> idQuDelete;

        for (int i = 0; i < allUsers.size(); i++) {
            for (int j = 0; j < allUsers[i].quFromMe.size(); j++) {
                if (allUsers[i].quFromMe[j].id == idQuDelete) {
                    allUsers[i].quFromMe[j].deleteQuestion(idQuDelete);
                }
            }
            for (int j = 0; j < allUsers[i].quToMe.size(); j++) {
                if (allUsers[i].quToMe[j].id == idQuDelete) {
                    allUsers[i].quToMe[j].deleteQuestion(idQuDelete);
                }
            }
        }
    }


    void systemAskQuestion() {
        numberOfQu++;

        question add;
        add.id = numberOfQu; //ID question
        add.from = userNow.id; //ID FROM

        cout << "Please enter the recipient's ID and then enter the message you want to send" << endl;
        cout << "Very important note: plz Replace the spaces with the symbol _" << endl;
        cin >> add.to; //ID TO
        cin >> add.content; //

        allUsers[add.from-1].addQuFromMe(add);
        allUsers[add.to-1].addQuToMe(add);
    }

    void systemAddAnswer() {
        numberOfAnswer++;

        cout << "Please enter the id of the question you want to send an answer to" << endl;
        int aid_id;
        cin >> aid_id;

        cout << "Pleas enter the answer" << endl;
        string aid_anwser;
        cin >> aid_anwser;
        for (int i = 0; i < allUsers.size(); i++) {
            for (int j = 0; j < allUsers[i].quFromMe.size(); j++) {
                if (allUsers[i].quFromMe[j].id == aid_id) {
                    allUsers[i].quFromMe[j].addAnswer(aid_anwser);
                }
            }
            for (int j = 0; j < allUsers[i].quToMe.size(); j++) {
                if (allUsers[i].quToMe[j].id == aid_id) {
                    allUsers[i].quToMe[j].addAnswer(aid_anwser);
                }
            }
        }
    }

    void systemFeed() {
        bool visited[1000] = {0}; //visited question by id
        for (int i = 0; i < allUsers.size(); i++) {
            for (int j = 0; j < allUsers[i].quFromMe.size(); j++) {
                if (!visited[allUsers[i].quFromMe[j].id]) {
                    if (allUsers[i].quFromMe[j].answer.size()) {
                        allUsers[i].quFromMe[j].printQuestion();
                        visited[allUsers[i].quFromMe[j].id] = true;
                    }
                }
            }
            for (int j = 0; j < allUsers[i].quToMe.size(); j++) {
                if (!visited[allUsers[i].quToMe[j].id]) {
                    if (allUsers[i].quToMe[j].answer.size()) {
                        allUsers[i].quToMe[j].printQuestion();
                        visited[allUsers[i].quToMe[j].id] = true;
                    }
                }
            }
        }
    }
};

int main() {

    system test;

    while (true) {
        cout << "plz enter [1-2]" << endl;
        cout << "1: login" << endl;
        cout << "2: sign up" << endl << endl;
        int n;
        cin >> n;

        if (n==1) {
            test.systemLogin();
        }
        else if (n==2) {
            test.systemSignUp();
            continue;
        }
        else {
            cout << "error" << endl;
            continue;
        }

        while (true) {

            cout << "plz enter [1-8]" << endl;
            cout << "1: print questions to me" << endl;
            cout << "2: print questions from me" << endl;
            cout << "3: answer question" << endl;
            cout << "4: delete question" << endl;
            cout << "5: ask question" << endl;
            cout << "6: list system users" << endl;
            cout << "7: feed" << endl;
            cout << "8: logout" << endl;
            cout << "9: exit" << endl;

            int enter;
            cin >> enter;
            if (enter==1) {
                test.systemPrintTomMe();
            }
            else if (enter==2) {
                test.systemPrintFromMe();
            }
            else if (enter==3) {
                test.systemAddAnswer();
            }
            else if (enter==4) {
                test.systemDeleteQu();
            }
            else if (enter==5) {
                test.systemAskQuestion();
            }
            else if (enter==6) {
                test.systemPrintAllUsers();
            }
            else if (enter==7) {
                test.systemFeed();
            }
            else if (enter==8)  {
                break;
            }
            else if (enter==9) {
                return 0;
            }
            else {
                cout << "error" << endl << endl;
                continue;
            }
         }
    }

    return 0;
}
