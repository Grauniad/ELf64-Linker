Archive Library (libArchive)
============================

Archive object (arc.h)
-----------------------
Helper object to read in an archive file and break into component files.

All reading is done through the IOIInterface library

### Usage
1. Creating the object initialises it and parses the library
2. You can now access Individual files by indexing the object

### Example
    // file is some binary reader object
    Archive arc = Archive(file);
    for( int i=0; i< arc.Count(); i++ ) {
       string fname = arc[i].Name();
       BinaryReader r = arc[i].Begin();
       unsigned char * data = r.Dup(arc[i].Size());
       cout  >> "Raw data for file: " <<  fname <<  endl;
       cout << data << endl;
       // ...
       delete [] data;
    }
