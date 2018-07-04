# Schedulability_Analysis_Tool_for_Hierarchical_Real_Time_Components
Extension of schedulability analysis tool for hierarchical real-time components developed by the Professor Luca Abeni. The extensione aims to add to the tool an analysis in case of EDF and multi-CPU partitioned scheduling.

## About 
This work has been realized in University of Pisa/Scuola Superiore Sant'Anna in the context of Component Based Software Design exam.

## Path and dependency
```
Schedulability_Analysis_Tool_for_Hierarchical_Real_Time_EDF_and_FP_Components/
├──vm
├──taskset_auto_generated
├──taskset_hand_generated
├──vm_hand_generated
├──report
├──bin
├──lib
└──src

=======
vm_hand_generated		 	-> files containing vm declarations for testing
=======
taskset_auto_generated		 -> files containing taskset (randomly generated) declarations for testing
=======
taskset_hand_generated		 -> files containing taskset declarations for testing
=======
report 		-> report of the project
=======
bin 		-> executables produced from the source files
=======
lib 		-> libraries included in the source code
=======
src 		-> source code
=======
```

## Authors
* <b>Silvio Bacci</b>

The same list can be found also in the <a href="https://github.com/ciabbi94/Schedulability_Analysis_Tool_for_Hierarchical_Real_Time_Components/graphs/contributors">contributors of this project.</a>

## License and citation
The project comes with an Apache 2 license. Of you want to use this code, you can do without limitation but you have to document the modifications and include this license. If you want to cite, please refer to:

```
@misc {
bacci2018,
author = "Silvio Bacci",
title = "Schedulability Analysis Tool for Hierarchical Real Time Components",
year = 2018,
address = "Pisa"
}
```



