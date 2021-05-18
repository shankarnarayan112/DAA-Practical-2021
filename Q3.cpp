#include<iostream>
int n,comp;
using namespace std;
void insertionSort(int ar[],int n){
	int ct=0,t,j;
	for(int i=1;i<n;i++)
	{
		t=ar[i];
		for(j=i-1;j>=0&&t<ar[j];j--)
		{
			ar[j+1]=ar[j];
			ct++;
		}
		
    	ar[j+1]=t;
	}
	cout<<"\nSorted array is:";
	for(int i=0;i<n;i++)
	{
		cout<<" "<<ar[i];
	}
	cout<<"\nNo of Comparisions : "<<ct;
}
void bubbleSort(int ar[],int n){
	int ct=0,temp=0,i;
	for(int i = 0; i<n; i++) {
   for(int j = i+1; j<n; j++)
   {
      if(ar[j] < ar[i]) {
         temp = ar[i];
         ar[i] = ar[j];
         ar[j] = temp;
      }
   }
   ct++;
}
	cout<<"\nSorted array:";
for(i = 0; i<n; i++) {
   cout <<ar[i]<<" ";
}
	cout<<"\nComparisions : "<<ct;
}

int findSmallest(int ar[],int i,int n)  
{  
    int ele_small,position,j;  
    ele_small = ar[i];  
    position = i;  
    for(j=i+1;j<n;j++)  
    {  
        if(ar[j]<ele_small)  
        {  
            ele_small = ar[j];  
            position=j;  
        }  
    }  
    return position;  
}

void selectionSort(int ar[],int n){
	int temp=0,pos=0,ct=0;
	for(int i=0;i<n;i++)  
    {  
        pos = findSmallest(ar,i,n);  
        temp = ar[i];  
        ar[i]=ar[pos];  
        ar[pos] = temp; 
        ct++;
    }  
	cout<<"\nSorted array is:";
    for(int i=0;i<n;i++)  
    {  
        cout<<ar[i]<<" ";  
    } 
    	cout<<"\nComparisions : "<<ct;
}
void merge(int a[],int i1,int j1,int i2,int j2,int n)
{
	int temp[50];
	int i,j,k;
	i=i1;	
	j=i2;	
	k=0;
	
	while(i<=j1 && j<=j2)	
	{
		if(a[i]<a[j])
		{
		
			temp[k++]=a[i++];
			comp++;
		}
		else
		{
			temp[k++]=a[j++];
			comp++;
		}
	}
	
	while(i<=j1)	
		temp[k++]=a[i++];
		
	while(j<=j2)	
		temp[k++]=a[j++];
		
	
	for(i=i1,j=0;i<=j2;i++,j++)
	{
			a[i]=temp[j];
}
	
	
}

void mergeSort(int a[],int i, int j ){
	int mid;
		
	if(i<j)
	{
		mid=(i+j)/2;
		mergeSort(a,i,mid);		
		mergeSort(a,mid+1,j);	
		merge(a,i,mid,mid+1,j,n);
	}
	
}
int partition(int a[],int l,int u)
{
	int p,i,j,temp;
	p=a[l];
	i=l;
	j=u+1;
	do{
		do
		i++;
		while(a[i]<p && i<=u);
		do
		j--;
		while(p<a[j]);
		if(i<j)
		{
		 temp=a[i];
		 a[i]=a[j];
		 a[j]=temp;
		}
		comp++;
	}while(i<j);
	a[l]=a[j];
	a[j]=p;
	return(j);
}

void quickSort(int a[],int i,int j)
{
	int mid;
	if(i<j)
	{
	mid=partition(a,i,j);
	quickSort(a,i, mid-1);
	quickSort(a,mid+1,j);	
	}
	
}
int main(){
	int ar[30],ch,n;
    cout<<"\nEnter number of elements to be sorted:\n";
    cin>>n;
    cout<<"\nEnter "<<n<<" elements to be sorted:\n";
    for (int i = 0; i < n; i++) { 
	cin>>ar[i];
    }
    cout<<"\nEnter the sorting technique to be used\n";
    cout<<" 1. Bubble Sort\n";
    cout<<" 2. Selection Sort\n";
    cout<<" 3. Insertion Sort\n";
    cout<<" 4. Merge Sort\n";
    cout<<" 5. Quick Sort\n";
    cin>>ch;
    switch(ch){
    	case 1:
    		bubbleSort(ar,n);
    		break;
    	case 2:
    		selectionSort(ar,n);
    		break;
    	case 3:
    		insertionSort(ar,n);
    		break;
    	case 4:
    		mergeSort(ar,0,n-1);
    		cout<<"\nsorted array is:\n";
	for(int i=0;i<n;i++)
	{
		cout<<" "<<ar[i];
	}
	cout<<"\nTotal number of comparisons are: "<<comp;
    		break;
    	case 5:
    		quickSort(ar,0,n-1);
    		cout<<"\nsorted array is:\n";
	for(int i=0;i<n;i++)
	{
		cout<<" "<<ar[i];
	}
	cout<<"\nTotal number of comparisons are: "<<comp;
    		break;
    	default: cout<<"Wrong choice ";
	}
	return 0;
}
