#include "../matrix.h"
#include "Nmap.h";
#define VAR gimp_image

int main(int argc, char** argv) {

  unsigned char * a;
  fstream file;
  int x,i,j,n,k;
  if (argc == 2) {
    file.open(argv[1],ios::out);
    n = (gimp_image.width * gimp_image.height * 4);
    file << (int) gimp_image.width << " "
	 << (int) gimp_image.height << endl;
    i =0;
    j =0;
    a = (unsigned char *) & gimp_image.pixel_data[0];
    while(i<n){
      k = (int) a[j];
      j++;
      /*      if( k & 128) {
	k = k - 128;
	do {
	  for(x=j;x<(j+4);x++){
	    file << (int) a[x];
	    if ((0 == (i % gimp_image.width)) && i !=0){
	      file << endl;
	    } else {
	      file << " ";
	    }
	    i++;
	  }
	}
	while(--k);
	j = x;    
      } else {
      */	k *=4; 
	for(x=j;x<j+k;x++){
	  file << (int) a[x];
	  if ((0 == (i % gimp_image.width)) && i !=0){
	    file << endl;
	  } else {
	    file << " ";
	  }
	  i++;
	}
	j=x;
	// }
    }
    file.close();
    return(0);
    } else {
    cout << "WRONG NUMBER OF ARGS: \ndecode filename\n";
    return(1);
  }
}

   
  
