// DS2 ex1
// 10427226 ��ĵ�W
// 10427210 ���Y��

#include <cstdlib>
#include <cstring>
#include <stdio.h>     // C  printf scanf
#include <stdlib.h>    // atoi  (char array to integer)
#include <iostream>    // C++ cout cin
#include <new>         // �ʺA�t�m
#include<fstream>      // C++ Ū��
#include <string.h>
#include <vector>
#include <math.h>
using namespace std;

string   fileName ;    // Ū�ɦW(�Ʀr)
string   number ;      // �����ɦW(�Ʀr)
int mission = 0;       // Ū�J����
int check = 0 ;        // 0 ��l�� �A 1 ����� �A 2 �L��ƽЭ��s��J�C
int gPrint = 0;
string  gSchool;
string  gDepartment;
string  gDay_or_night;
string  gRank;

typedef struct Heap
{   int i ;            // �y���s��
    int quantity_student;
}  ha;

typedef struct cT
{   string  number_school;
    string  school;
    string  department;
    string  day_or_night;
    string  rank;
    int     quantity_student;
}   collegeType;



bool load( vector<collegeType> & ) ;               // Ū��
void filter(vector<collegeType> & ) ;              // �z��(���Ȥ@)
void need () ;                                     // �z�����
void print() ;                                     // �L�X
void heapInsert () ;                               // ��min heap
vector<collegeType> gAnswer;                       // �z��ᵲ�G
vector<ha> heap;                                   // min heap
vector<ha> kheap ;
void swapheap( int , int ) ;
bool IsOddFloor( int ) ;                           //�P�_�h��
void case2(int ) ;                                 // �� �ܩ��㪺case2
void rebulid(int) ;                                //���s�ؾ�
void printKans() ;

int main(void){
  cout << "�w��ϥΦ��{��!\n" ;
  vector< collegeType >     cSet;                  // set of output records
  cout << "��J'1'�A�̷ӫ��w���z������\n"
		  "��J'2'�A�Y�������{���C\n";
  cin >> mission ;
  int Nnum = 0 ;
  while ( mission < 2 && mission > 0 ) {
    load(cSet);                                    // Ū��
    if ( check == 1 ) {                            // �T�{�O���Ī��ɦW
         need();
         filter(cSet);
         print();
         if ( check == 1 && gAnswer.size() != 0 )  {       // �p�G�S����� �N���i�h����2
           heapInsert() ;
           cout << "��Jn���̤j���       "  ;
		   cin >> Nnum ;
		   case2( Nnum);
		   printKans() ;
         }
         else if( check == 2 ) ;
         else
		   cout << "0����Ƥ�����heap" ;
    } // if

    cout << "\n�Y�Q�~��ϥΡA�ЦA����J���O�C\n"
            "��J'1'�A�̷ӫ��w���z������\n"
            "�Y�L�A�Ы�'2'�����{��\n"  ;
    cSet.clear();
    gAnswer.clear() ;
    heap.clear() ;
    kheap.clear() ;
    check = 0;
    cin >> mission ;

  } // while

  //system("pause");
  return 0;
}	// end main

void rebulid(int place ){
   while ( place < heap.size() && place != 0  ){
     int leftson = place * 2 + 1, rightson = leftson + 1,llgson = leftson *2 +1 ;    //���� �k�� �����]
     int lrgson = llgson +1 , rlgson = lrgson +1, rrgson = rlgson +1 ;               // ���k�] �k���] �k�k�]
     int findGson = 0 ;
                                                                                     // ���ˬd��l���S����L�j��
     if ( leftson < heap.size() ) if( heap[leftson].quantity_student > heap[place].quantity_student ) swapheap( leftson,place ) ;
     if ( rightson < heap.size() ) if( heap[rightson].quantity_student > heap[place].quantity_student ) swapheap( rightson,place ) ;
                                                                                     // �ˬd�]�l���S����L�j��
     if ( llgson < heap.size() )  findGson = llgson ;                                //��X �]�l���̤j��
     if( lrgson < heap.size() && heap[findGson].quantity_student < heap[lrgson].quantity_student ) findGson = lrgson ;
     if( rlgson < heap.size() && heap[findGson].quantity_student < heap[rlgson].quantity_student ) findGson = rlgson ;
     if( rrgson < heap.size() && heap[findGson].quantity_student < heap[rrgson].quantity_student ) findGson = rrgson ;
     if ( findGson != 0 && heap[findGson].quantity_student > heap[place].quantity_student ) swapheap( place,findGson ) ;
     place = findGson ;
    }//while()
}

void case2( int num ){
    for( int k = 0 ; k < num ; k ++ ) {
      int test = 0 ;                                                 //�����ڮ������٬O�k�䪺
      if ( heap[1].quantity_student > heap[2].quantity_student ) {   //�P�_����j ���j�����Ჾ��̥k�U��
      	kheap.push_back( heap[1] ) ;
      	swapheap( 1, heap.size()-1 ) ;
      	test = 1 ;
      }
      else {
	    kheap.push_back( heap[2] ) ;
	    swapheap( 2, heap.size()-1 ) ;
	    test = 2 ;
	  }
	  heap.pop_back() ;  //�R���̫�@��
	  rebulid( test ) ;
	  test = 0 ;
    }

}
bool load( vector<collegeType> &cSet ) {                    // �t�dŪ�J�ɮת�function
    fstream infile ;
    string name ;
    char *buffer = new char[255] ;                          // �ʺA�t�m�@��char array�ΨӼȦsŪ�J���F��
    while ( 1) {
      cout << "\n�п�J�ɮצW�� : \n" ;
      cin >> name ;                                         // Ū�J�ɮת��W�r
      name = "input" + name + ".txt" ;
      infile.open( name.c_str(), fstream::in ) ;            // �}���ɮ�
      if ( !infile ) {                                      // �p�G�L�k�}�Ҫ�������load
          cout << name << "�ɮפ��s�b" << endl ;
          check == 2;
      }
      else break ;
    }

    for ( int i = 0 ; i < 3 ; i++ )                         // �e�T��ëD�n����ƪ���Ū�������z�|
        infile.getline( buffer, 255 ) ;
    delete [] buffer ;                                      // �M��buffer�����F��
    buffer = new char[255] ;

    int pre = 0, pos = 0 ;

    while(  !infile.eof() ) {                               // �Y�D��Ƶ����h�~��j��
        infile.getline( buffer, 255 ) ;                     // Ū�J�����
        collegeType one ;                                   // �Ȧs���Χ������
         int pre = 0, pos = 0 ;                             // pre�s����r�ꪺ�_�l��m   pos�s�̫��m
        string temp ;                                       // �s�নString��buffer
        temp.assign( buffer ) ;                             // buffer��string
        int switch_count = 0 ;                              // ���U���j�骺switch�p�ƥ�
        bool check2 = true ;                                // �T�{�U�����j��O�_�~��

        while ( check2 ) {                                  // ���j��ΨӤ���Ū�J�������
            pos = temp.find_first_of( '\t', pre ) ;         // ���U�@��\t����m�s�bpos

            switch( switch_count++ ) {
                case 1 :                                    // �Ǯսs���s�Jone
                    one.number_school = temp.substr( pre, pos - pre ) ;
                    pre = pos + 1 ;
                    break ;
                case 2 :                                    // �ǮզW�٦s�Jone
                    one.school = temp.substr( pre, pos - pre ) ;
                    pre = pos + 1 ;
                    break ;
                case 3 :                                    // ��t�N�X���ݭn�����z�|
                    pre = pos + 1 ;
                    break ;
                case 4 :                                    // ��t�W�٦s�Jone
                    one.department = temp.substr( pre, pos - pre ) ;
                    pre = pos + 1 ;
                    break ;
                case 5 :                                    // ��]�O�s�Jone
                    one.day_or_night = temp.substr( pre, pos - pre ) ;
                    pre = pos + 1 ;
                    break ;
                case 6 :                                    // ���ŧO�s�Jone
                    one.rank = temp.substr( pre, pos - pre ) ;
                    pre = pos + 1 ;
                    break ;
                case 7 :                                    // �ǥͼƦs�Jone
                    one.quantity_student = atoi(temp.substr( pre, pos - pre ).c_str()) ;
                    pre = pos + 1 ;
                    check2 = false ;
                    break ;
                default :
                    break ;
            }
        } // in_while
        if(one.day_or_night.empty() || one.department.empty() || one.number_school.empty()
		   || one.rank.empty() || one.school.empty() || one.quantity_student == 0 )
		   int h = 0;
        else
           cSet.push_back( one ) ;                          // �None��JcSet�o��vector������

    } // out_while

    infile.close() ;
    check = 1 ;
    if (!cSet.size()) {
        cout << endl << "### Get nothing from the file " << fileName << " ! ### " << endl;
        check = 2 ;
    } // if
}

void need() {
    cout << "\nEnter a keyword of �ǮզW��: [*]for all\n";
    cin >> gSchool;
    cout << "Enter a keyword of ��t�W��: [*]for all\n";
    cin >> gDepartment;
    cout << "Enter a keyword of ��]�O: [*]for all\n";
    cin >> gDay_or_night;
    cout << "Enter a keyword of ���ŧO: [*]for all\n";
    cin >> gRank;
}

void print() {
     cout << "\n�@��" << gAnswer.size() << "�����" << endl ;
	 int i = 0;
	 while( i < gAnswer.size()) {
	     cout << "[" << i+1 << "]" << gAnswer[i].school << gAnswer[i].department << ", " ;
         cout << gAnswer[i].day_or_night << ", " << gAnswer[i].rank << ", " << gAnswer[i].quantity_student << endl ;
         i = i + 1;
     }
}

void printKans() {
  for ( int i = 0 ; i < kheap.size() ; i++ ) {
     cout << "Top  " << i+1 << ":[" <<  kheap[i].i+1 << "]  " << gAnswer[kheap[i].i].school << gAnswer[kheap[i].i].department << ", ";
     cout << gAnswer[kheap[i].i].day_or_night << ", " << gAnswer[kheap[i].i].rank << ", " << gAnswer[kheap[i].i].quantity_student << endl;
  }
}


void filter(vector<collegeType> &aSet){
    vector<collegeType> tempS(aSet);                      // a copy of the entire vector (array)
    collegeType answer ;
    int i = 0;
    for( ; i < tempS.size() ; i ++  )                     // �@������Ʃ��U�� �����z�����ŦX�N�L�X
        if ( gSchool == "*" || strstr( tempS[i].school.c_str(),gSchool.c_str()) != NULL )
           if ( gDepartment == "*" || strstr( tempS[i].department.c_str(), gDepartment.c_str() ) != NULL)
              if ( gDay_or_night  == "*" || strstr( tempS[i].day_or_night.c_str(), gDay_or_night.c_str() ) != NULL )
                 if ( gRank == "*" || strstr( tempS[i].rank.c_str(), gRank.c_str() ) != NULL )
                 	gAnswer.push_back( tempS[i] ) ;       // ��ŦX��ƪ���J���ץe�s
} // �z��  { if (size >= MAX_HEAP)

void swapheap( int sparent, int splace ){
  Heap temp;
  temp.i = heap[sparent].i;
  temp.quantity_student = heap[sparent].quantity_student;
  heap[sparent].i = heap[splace].i;
  heap[sparent].quantity_student = heap[splace].quantity_student;
  heap[splace].i = temp.i;                        // swap items[place] and items[parent]
  heap[splace].quantity_student = temp.quantity_student;
}

bool IsOddFloor( int number ) {
  int total = 0, floor = 0  ;                               // floor+1�O�ثe�h��
  for (;  total < number; floor ++ )  total = total + pow( 2, floor ) ;	    	            // pow�� �p�⦸�誺����
  if( floor % 2 != 0 ) return true ;                        // �j�鵲���w�g�۰�+1 �����A�S�O�`�N
  else return false ;
}
void heapInsert () {
	int i = 0;
	while(i < gAnswer.size() ) {
		Heap put;
	    put.i = i;
	    put.quantity_student = gAnswer[i].quantity_student ;
	    heap.push_back( put ) ;

        int place = heap.size()-1;               // �l�`
        int parent = ( place - 1) / 2; //���`
   	    int grandparent = ( parent -1 ) / 2 ;    //����
        while ( place - 1 > 0 ){
		  bool IsOdd = IsOddFloor( place +1)  ;                // �P�_�h�ƬO�H1�}�l �ҥH�n+1
		  if ( !IsOdd ) {                                      // ���Ƽh
		  	if ( heap[place].quantity_student < heap[parent].quantity_student )
                swapheap( parent,place ) ;
		  	if ( place != 0 && parent != 0 )                   //�O�_������
			  if ( heap[place].quantity_student > heap[grandparent].quantity_student )
                swapheap( grandparent,place ) ;
		  }
		  else{  //�_�Ƽh
		  	if ( heap[place].quantity_student > heap[parent].quantity_student ) swapheap( parent,place ) ;
		  	if ( place != 0 && parent != 0 )
			  if ( heap[place].quantity_student < heap[grandparent].quantity_student )	swapheap( grandparent,place ) ;
		  }
          place = parent;
          parent = (place - 1)/2;
          grandparent = ( parent -1 ) / 2 ;
        } // end while
        i = i + 1;
      }
	  int total = 0, floor = 0  ;                               // floor+1�O�ثe�h��
      for (;  total < i-1  ; floor ++ )  total = total + pow( 2, floor ) ;	    	            // pow�� �p�⦸�誺����
      total = 0 ;    //�p��h��
 	  for ( int k = 0 ; k < floor -1  ; k ++ ) total = total + pow( 2, k ) ;                               //�μh�ƥh��̥��䪺���X
      cout << "����(�k�U): [" << heap[i-1].i+1 << "]  " << heap[i-1].quantity_student << endl;
	  cout << "����(���U): [" << heap[total].i+1 << "]  " << heap[total].quantity_student << endl;
      //for ( int qq= 0 ; qq < heap.size() ; qq ++ ) {
      //	cout << qq << "  " << heap[qq].quantity_student << endl ;
      //}
} // end heapInsert








