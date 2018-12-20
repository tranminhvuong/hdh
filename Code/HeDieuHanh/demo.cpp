#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;
int total_time = 0;
float avgtat=0,avgwt=0;
//varibble for round_bind
int time = 0, front = 0, rear = 0, q_count = 0, m = 0, s = 0;
int queue[1000];
int ii,jj;
//end variable for round bind

struct data
{
int at,st,ct,tat,wt;
char pname[20];
float ntat;
int pr; //priority
}temp;
// function for round bind
void RR_finding(struct data a[],int n);
void push(int q) ;
int pop();
void check(struct data a[],int n);
//end function for round bind

void input(struct data aa[],int n);
void SJF_finding(struct data a[],int n);
void FCFS_finding(struct data a[],int n);
void PRI_finding(struct data aaa[],int n);
void PRI_display(struct data a[],int n);
void print_gantt(struct data a[],int n);
void display(struct data a[],int n);

int main(){

  char k;// kiem tra lua chon
  int n;// so tien trinh

  cout<< "Nhap so luong tien trinh: ";
  cin>>n;
  struct data a[n];
  cout<<"\nNhap thong tin tien trinh: \n\n\n";
  input(a,n);
  //Total_time
    total_time+=a[0].at+a[0].st;
    for(int i=1;i<n;i++)
    {
    if(a[i].at>total_time) total_time=a[i].at;//coz if the next process arives after a while after the b4 process has //complted
    total_time+=a[i].st;
    }
  //END total_time

    label:
    do{
    cout << "\n\tChon thuat toan";
    cout << "\n\t1. Thuat toan FCFS";
    cout << "\n\t2. Thuat toan SJF";
    cout << "\n\t3. Thuat toan Priority";
    cout << "\n\t4. Thuat toan RR";
    cout << "\n\t5. Thoat chuong trinh";

    cout << "\n\t Ban chon: ";
    cin >> k;
  } while (k == '5');
  if (k == '5') exit(0);
  if (k != 5) {
    if (k == '1') {
      cout<<endl<<endl<<"Thong tin lap lich theo thuat toan FCFS: \n\n:";
      FCFS_finding(a,n);
    } else if (k == '2') {
       cout<<"Thong tin lap lich theo thuat toan SJF: \n\n:";
      SJF_finding(a,n);
    } else if (k == '3') {
        for(int i = 0;i<n;i++){
            printf("Nhap do uu tien cua tien trinh %s: ", a[i].pname);
            scanf("%d",&a[i].pr);
        }

        PRI_finding(a,n);
    } else if (k == '4') {

      RR_finding(a,n);
    } else {
      exit(0);
    }
  }
   if(k!= '4')
   {
    cout<<endl;
    cout<< "So do gantt:";
    print_gantt(a,n);
   }
   cout<<endl<<endl<<"Ban co muon chon giai thuat khac:";
   char kt;
   cin>>kt;
   if(kt == 'y'){
    avgtat=0,avgwt=0;
    goto label;

   }

  cout<<endl<<endl;
  return 0;
}
void input(struct data aa[],int n)
{

    struct data temp;
    for(int i=0;i<n;i++)
    {
        printf("Nhap ten tien trinh %d ,thoi gian den, thoi gian thuc hien[ Ex: p1 0 5]:\n",i+1);
        scanf("%s",&aa[i].pname);
        scanf("%d%d",&aa[i].at,&aa[i].st);
    }
//sorting
	for(int i=0;i<n;i++)
	{
		for(int j=i;j>=1;j--)
		{
			if(aa[j].at<aa[j-1].at)
			{
			temp=aa[j-1];
			aa[j-1]=aa[j];
			aa[j]=temp;
			}
		}
	}
}
void SJF_finding(struct data a[],int n)
{
	int time_count=0,c;//,procs[n];//c is for counter and procs is to atore the processes that arived
	int i =0,j = 0;
	while(time_count<total_time)
	{
        c=0;
        j=0;
        for(i=0;i<n;i++)
        {	if(a[i].at<=time_count)
            {
                j=i+1;
            }//storing the list of processes that have arrived
        }
        if(j>0)
         {
            int x=0,min_st=a[0].st;
            for(i=1;i<j;i++)
            {
                if(min_st>a[i].st)
                {
                    x=i;
                    min_st=a[i].st;
                }
            }// tìm ra tiến trình có thời gian thực hiện ngắn nhất
            time_count+=a[x].st;//x is the process with min service time
            a[x].ct=time_count;
            a[x].st+=1000;//thiết lập st lớn để nó không được lựa chọn để so sánh nữa
         }
        else
          {
            time_count++;
          }
	}
	for(i=0;i<n;i++)
      {
        a[i].st-=1000;// Khôi phục lại giá trị thời gian thực hiện ban đầu của tiến trình
      }//

    display(a,n);
}
// FSFS_finding
void FCFS_finding(struct data a[],int n)
{
int stt=a[0].at,tempi;
a[0].ct=stt+a[0].st;
stt=a[0].ct;
for(int i=1;i<n;i++)
{
tempi=a[i].at;
if(tempi>stt)
stt=tempi;
a[i].ct=stt+a[i].st;
stt=a[i].ct;
}
display(a,n);
}
//PRI_finding
void PRI_finding(struct data a[],int n) {

  int time = 0; //Biến đếm thời gian,chạy từ  0 đến total_time-1,tăng lên 1

  int i,j;
  while (time < total_time) {
    j = 0;// Thiết lập lại j = 0
    for (i = 0; i < n; i++) {
      if (a[i].at <= time) {
        j = i + 1;
      } //lưu danh sách các tiến trình đã đến

    }
    if (j > 0) {
      int x = 0, min_pr = a[0].pr; //min priority
      for (i = 1; i < j; i++) {
        if (min_pr > a[i].pr) {
          x = i;
          min_pr = a[i].pr; // Thiết lập độ ưu tiên cao nhất
        } else if (min_pr == a[i].pr)
          if (a[x].at > a[i].at) {
            x = i;
            min_pr = a[i].pr;//Nếu cùng độ ưu tiên thì tiến trình nào đến sớm hươn thì min_pr = độ ưu tiên của tiến trình đó
          } else if (a[x].at == a[i].at) {
            if (a[x].st > a[i].st) {
              x = i;
              min_pr = a[i].pr;// Nếu cùng thời gian đến luôn thì min_pr = độ ưu tiên của tiến trình có thời gian xử lí nhỏ hơn
            }
          }

        }//end for, kết thúc vòng for này, tiến trình nào đạt 3 tiêu chí: độ ưu tiên, thời gian đến sớm, thời gian xử lí ít nhất
       //Trong các tiến trình đã đến được lựa chọn để cấp CPU
      time += a[x].st; //time += thời gian thực thi của tiến trình đã chọn ở trên
      a[x].ct = time; // Thời gian hoàn thành tiến trình vừa chọn = time
      a[x].pr += 1000; //thiết lập độ ưu tiên để ko chọn lại khi lặp lại vòng lặp, loại bỏ tiến trình này, ko so sánh nữa
      a[x].at += 1000; //thiết lập thời gian đến lớn để ko dựa vào thời gian đến của nó để lựa chọn nửa

    }else {
      time++; // Khi các tiến trình chưa dến thì tăng time lên 1 đơn vị

    }

  }
  for (i = 0; i < n; i++) {
    a[i].pr -= 1000;
    a[i].at -= 1000;
  } // Thiết lập lại giá trị ban đầu của các tiến trình
  PRI_display(a,n);
}

//display
void display(struct data a[],int n)
{
int i,j;
for( i=0;i<n;i++)
{
    a[i].tat=a[i].ct-a[i].at;
    a[i].wt=a[i].tat-a[i].st;
    a[i].ntat=(float)a[i].tat/a[i].st;
    avgtat+=a[i].tat;
    avgwt+=a[i].wt;
    }
    avgtat=avgtat/n;
    avgwt=avgwt/n;
    printf("pname\tat\tst\tct\ttat\twt\tntat\n");
    for(i=0;i<n;i++)
    {
    printf("%s\t%d\t%d\t%d\t%d\t%d\t%f\n",a[i].pname,a[i].at,a[i].st,a[i].ct,a[i].tat,a[i].wt,a[i].ntat);
    }
    printf("avgtat=%f\navgwt=%f\n",avgtat,avgwt);
}

//PRI_display
void PRI_display(struct data a[],int n) {
   cout<<endl<<endl<<"Thong tin lap lich theo thuat toan Do uu tien: \n\n";
  int i =0,j = 0;
  for (i = 0; i < n; i++) {
    a[i].tat = a[i].ct - a[i].at;
    a[i].wt = a[i].tat - a[i].st;
    a[i].ntat = (float) a[i].tat / a[i].st;
  }
  for (i = 0; i < n; i++) {
    avgtat += a[i].tat;
    avgwt += a[i].wt;
  }
  avgtat = avgtat / n;
  avgwt = avgwt / n;
  printf("pririty\tpname\tat\tst\tct\ttat\twt\tntat\n");
  for (i = 0; i < n; i++) {
    printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%f\n", a[i].pr, a[i].pname, a[i].at, a[i].st, a[i].ct, a[i].tat, a[i].wt, a[i].ntat);
  }
  printf("avgtat=%f\navgwt=%f\n", avgtat, avgwt);

}
//print_gantt
void print_gantt(struct data a[],int n)
{
    int i,j;
    struct data tam[n] ;
    struct data tg;
    for( i = 0;i<n;i++){
        tam[i] = a[i];
    }
    // Sap xep theo ct tang dan
    for (i = 0; i < n-1; i++) // Sắp xếp các tiến trình theo thời gian xuất hiện tăng dần
    {
          int min = i;
          for (j = i+1; j < n; j++)
            {
                if (tam[j].ct < tam[min].ct)  min = j;

            }
         if(min != i){
              tg = tam[i];
              tam[i] = tam[min];
              tam[min] = tg;
         }
    }
    for(int i = 0;i<n;i++)
    {
        if(i == 0) printf("%d",tam[i].at);
        else printf("%d",tam[i-1].ct);
        printf(" %s ",tam[i].pname);
    }
    printf(" %d",tam[n-1].ct);

}

//round bind
void push(int q) {
  queue[rear++] = q;
  //rear%=n;
  m++;
}
int pop() {
  s++;
  int x;
  x = queue[front++];

  return x;
}

void check(struct data a[],int n) {
  while (a[jj].at <= time && jj < n) //coz all tthe process must b checked b4 pushing the presently executed process into the queue
  {
    q_count++;
    push(jj++);
  }
}

void RR_finding(struct data a[],int n) {

  int temp_st[n], flag = 0, count = 0, p_process; //p_process là tiến trình hiện tại, flag để đánh dấu tiến trình đó đã được chọn
  jj = 0;
  int tq;
  printf("enter the time quantum\n");
  scanf("%d", & tq);
  for (ii = 0; ii < n; ii++) {
    temp_st[ii] = a[ii].st;// Mảng tempt_st chứa thời gian thực hiện của các tiến trình
  }

  time = a[0].at;

  q_count = 1;
  push(jj++);
  while (time <= total_time) {
    if (flag == 1 || q_count != 0) //ie i enetrs if a process is already selected or a new process can be selected
    {
      if (flag == 0 && count == 0) {

        p_process = pop(); //queue[front];
        //p_process=i;
        count = 0;
        flag = 1;

      }
      temp_st[p_process]--;

      if (temp_st[p_process] == 0) {
        time++;
        count = 0;
        a[p_process].ct = time;
        flag = 0; //a[i].st+=1000;
        q_count--;
        check(a,n);
        continue;
      }
      count++;
      //count=count%tq;
      if (count == tq) {
        count = 0;
        time++;
        check(a,n);
        push(p_process);
        flag = 0;
      } else {
        time++;
        check(a,n);
      }
    } else {
      time++;
      check(a,n);
    }

  } //end of while loop
  cout<<endl<<endl<<"Thong tin lap lich theo thuat toan Round robin: \n\n:";
  display(a,n);
}

// end round bind



