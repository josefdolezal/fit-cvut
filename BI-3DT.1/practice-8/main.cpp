#include <stdlib.h>
#include <iostream>
#include <admesh/stl.h>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
  if( argc < 3 ) {
    cout << "No file specified." << endl;
    return 1;
  }

  double min_value  = 0;
  int    best_angle = 0;

  stl_file stl_in;
  char *filename = argv[1];
 
  cout << "Opening " << filename << endl;
  stl_open(&stl_in, filename);
  stl_exit_on_error(&stl_in);

  min_value = (double) stl_in.stats.size.x * stl_in.stats.size.y;
  cout << "Original area " << min_value << endl;

  for(int i = 5; i < 90; i+=5) {
    stl_rotate_z(&stl_in, 5);
    stl_exit_on_error(&stl_in);

    double curr_value = (double) stl_in.stats.size.x * stl_in.stats.size.y;
    cout << "Testing angle " << i << " " << curr_value << endl;

    if(curr_value < min_value) {
      min_value = curr_value;
      best_angle = i;
      
      cout << "New best area is " << setprecision(8) << min_value << " for angle " << i << endl;
    }
  }

  cout << "Best angle was " << best_angle << endl;
  
  stl_rotate_z(&stl_in, best_angle + 275);
  stl_exit_on_error(&stl_in);

  if (stl_in.stats.type == binary) {
    stl_write_ascii(&stl_in, argv[2], "ADMesh");
    stl_exit_on_error(&stl_in);
  } else {
    stl_write_binary(&stl_in, argv[2], "ADMesh");
    stl_exit_on_error(&stl_in);
  }

  stl_close(&stl_in);
  return EXIT_SUCCESS;
}
