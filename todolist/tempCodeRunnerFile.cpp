#include <iostream>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <conio.h>
#include<chrono>

using namespace std;
//menna
struct node{

chrono::system_clock::time_point time_added;
string data;
bool completed;
node* next;
bool warned;
node(string value){
    data=value;
    next=nullptr;
    warned=false;
    completed=false;
time_added = chrono::system_clock::now(); // وقت الإضافة
}
};
class tasks{
    node*head;
    node*tail;
    bool completion=false;
    int points=0;
    public:

    tasks(){
        head=tail=nullptr;

    }
       //add at the last
    void addtasks(string value,int indx){
//index 1-based
indx--;
if(indx<0){
cout<<"Invalid index try to add your new task on a place starts from 1\n";
return;
}
node*newnode=new node(value);
if(indx==0){
    //at the beginning
    newnode->next=head;
    head=newnode;
    if(tail==nullptr){
        tail=newnode;

    }
    return;//لازم بعد اضافة اول عنصر
}
node*temp=head;

for(int i=0;i<indx-1&&temp!=nullptr;i++){
temp=temp->next;

}
if(temp==nullptr){
    cout<<"Invalid place please try another place dear\n";
    return;
}
newnode->next=temp->next;
temp->next=newnode;
if(newnode->next==nullptr){
    tail=newnode;
}
    }
    void searchTask(string name) {
    node* current = head;
    int cnt = 1;
    bool found = false;
    while(current) {
        if(current->data.find(name) != string::npos) { // لو الاسم موجود

            cout << "Task " << cnt << ": " << current->data;
            if(current->completed) cout ;
            cout << endl;

            found = true;
        }
        current = current->next;
        cnt++;
    }
    if(!found) {

        cout << "Task not found!\n";

    }
}

    void display(){
 cout<<"           Your tasks until now         \n";
        node*current=head;
        int cnt=1;
while(current){
    cout<<cnt<<" : "<<current->data<<' ';
    if(current->completed) {

         cout <<"done" ;
         }
    cout<<endl;
    current=current->next;
    cnt++;}
    //ان فيه غلطه فى نظام النقط (Afnanِِِ)
     cout << "Your current points: " << points << endl;
if(points == 20)
        cout << " Congratulations! You've reached Super Tasker! \n";
    else if(points == 40)
        cout << " Amazing! You've reached Mega Tasker! \n";
    else if(points == 60)
        cout << " Incredible! You've reached Ultimate Tasker! \n";
cout<<endl;
    }
  void  deletebeg(){
        if(head==nullptr){
            cout<<"No tasks available\n";
            return;

        }
     else {  node*temp=head;
        head=head->next;
        if(head == nullptr) tail = nullptr;
        cout<<"First task deleted successfully\n";
        delete temp;}

    }
   void check_old_tasks() {
    auto now = chrono::system_clock::now();
    node*current = head;
    while(current){
        if(!current->completed && !current->warned)
{
            auto duration_sec = chrono::duration_cast<chrono::seconds>(now - current->time_added).count();
            if(duration_sec >= 3){ // 3 ثواني للتجربة
                cout << "WARNING! Task \"" << current->data << "\" has been pending for more than 3 seconds!\n";
                current->warned = true;

            }

        }
        current = current->next;
    }
}


    void del(int idx){
        idx--;
        if(idx<0){
            cout<<"Invalid position\n";
            return;

        }
      else  if(head==nullptr){
            cout<<"NO tasks available\n";
            return;
        }
        else if(idx==0){
deletebeg();
return;
        }
        else{
            node*temp=head;
           for(int i=0;i<idx-1 &&temp!=nullptr;i++) {
            temp=temp->next;
           }
if(temp->next==nullptr){
    cout<<"Position is not correct try anthor position please\n";
    return;
}
//لما نيجى نمسح اخر تاسك الtail مكنش بيتحدث فبيحصل مشكله لما نيجى نضيف بعد كده(Afnan)
        node*value=temp->next;
        temp->next=temp->next->next;
        if(temp->next==nullptr)
            tail=temp;
        delete value;}
    }
    string show(int idx){
        idx--;
        node*temp=head;
        if(idx<0){
          return  "Position is not correct try anthor position please\n";

        }
        for(int i=0;i<idx&&temp!=nullptr;i++){
            temp=temp->next;
        }
if(temp==nullptr){
   return "Task does not exist!";
}

return temp->data;
    }
    void clear(){

while(head){
    node*temp=head;
    head=head->next;
    delete temp;


}
tail=nullptr;
    }
    void mark_as_completed(int idx){
        //1-based
idx--;
if(idx<0){
    cout<<"Invalid task number\n";
    return;
}
node*temp=head;
for(int i=0;i<idx&&temp!=nullptr;++i){
    temp=temp->next;
}
        if(temp==nullptr){
            cout<<"No tasks available,please enter your tasks first\n";
        return;
        }
        if(temp->completed){
        cout << "Task already completed!\n";
        return;
    }
        //mark complete
        temp->completed=true;
        PlaySound("success.wav", NULL, SND_FILENAME | SND_ASYNC);


        points+=10;

        cout << " Great job! You completed a task! +10 points ✅\n";



    }
};
int main() {
    tasks myTasks;
    PlaySound("welcome.wav", NULL, SND_FILENAME | SND_ASYNC);


 cout<<"===============================Your Daily Task===============================================  "<<endl;
   cout<<"enter 1 :to add new task and give me the new  task  "<<endl;
  cout<<"enter  2:to delete specific task and give me task number "<<endl;
  cout<<"enter  3:to display your current points "  <<endl;
  //4 5 بيطلعوا نفس الرساله فى الاوت بوت فالمستخدم مش هيفهم(Afnan)
  cout<<"enter  4 to  :Show Task by number "<<endl;
  cout<<"enter  5:to remove all your tasks  "<<endl;
  cout<<"enter  6 to  :Search Task by name "<<endl;
  cout<<"enter 'space' in your keyboard:to mark task complete  "<<endl;
  cout<<"enter 'delete ' on your keyboard : to exit.  "<<endl;


 cout<<"=====================Small steps, big achievements!============================================= "<<endl;

while(true){
int first;
int task_number;
myTasks.check_old_tasks();
    if(_kbhit()){
        Beep(1000, 200);

        //there is a press
first=getch();
//if special character it return two codes
//first to show that it is special key
//second the code if this special key
if(first==0||first==224){
    //special key
    first=getch();
}
//32 represent المسطره
//83 represent "delete"

if(first==32){

cout<<"enter task completed number\n";
cin>>task_number;
//1 based
//mark_as_completed is not created yet



myTasks.mark_as_completed(task_number);

}
else if(first==83){
    cout << "Exiting program...\n";
    return 0;
}
else if(first=='1'){ // Add new task
            string name;
            int index;
            cout << "Enter task number: ";
            cin >> index;
            while(cin.fail()){
    cin.clear();            // يمسح حالة الخطأ
    cin.ignore(1000, '\n'); // يتجاهل أي إدخال غلط موجود في البفر
    cout << "Invalid input! Please enter a number: ";
    cin >> index;           // يطلب الإدخال مرة تانية
}

            cin.ignore();
            cout << "Enter task text: ";
            getline(cin, name);
            //(afnan)عشان يظهر رسالة ايرور لو المستخدم مدخلش اسم للتاسك
            while(name.empty()){
                    cout<<"Task name cannot be empty! Please enter a valid task: "<<endl;
                    PlaySound("invalid.wav", NULL, SND_FILENAME | SND_ASYNC);
                    getline(cin,name);
            }
            myTasks.addtasks(name, index);
            PlaySound("AddedTask.wav", NULL, SND_FILENAME | SND_ASYNC);
            cout<<"you added your task successfully!\n"<<endl;
        }
        else if(first=='2'){ // Delete task
            int index;
            cout << "Enter task number to delete: ";
            cin >> index;
            while(cin.fail()){
    cin.clear();            // يمسح حالة الخطأ
    cin.ignore(1000, '\n'); // يتجاهل أي إدخال غلط موجود في البفر
    cout << "Invalid input! Please enter a number: ";
    cin >> index;           // يطلب الإدخال مرة تانية
}

            myTasks.del(index);
            PlaySound("DeletedTask.wav", NULL, SND_FILENAME | SND_ASYNC);
            cout<<"Your deleted your task successfully"<<endl;
        }
        else if(first=='3'){ // Display tasks
            myTasks.display();
            PlaySound("points.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
        else if(first=='4'){ // Show task by index
            int index;
            cout << "Enter task number to show: ";
            cin >> index;
            while(cin.fail()){
    cin.clear();            // يمسح حالة الخطأ
    cin.ignore(1000, '\n'); // يتجاهل أي إدخال غلط موجود في البفر
    cout << "Invalid input! Please enter a number: ";
    cin >> index;           // يطلب الإدخال مرة تانية
}

            cout << "Task: " << myTasks.show(index) << endl;
            PlaySound("luvvoice.com-20251211-0AKASW.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
        else if(first=='5'){ // Clear all tasks
            myTasks.clear();
            cout << "All tasks removed successfully!\n";
        }
else if(first=='6'){
    // Add new task
    string tsk;
            cout<<"Enter task name to search: ";
            //مش بياخد غير اول كلمه بس(Afnan)
            cin.ignore();
            getline(cin,tsk);
            while(tsk.empty()){
                cout<<"task name can't be empty ,please try again"<<endl;
                getline(cin,tsk);
            }


           myTasks .searchTask(tsk);
        }
    }
}
    return 0;
}