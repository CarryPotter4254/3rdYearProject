# 3rd Year Project: Benchmarking SAT-Solvers via Necklace Splitting

This folder contains all the code used in this project.

- benchmarkcreation.cpp is the implementation to generate random input instances of the Splitting Necklace problem and combine them into a enchmark.

- projecttodimacscnf.cpp is the implementation to transform from a random input instances into a CNF formula in a SAT solver readable way.

- systemrun.cpp implements the runs of a SAT solver (can be specified by altering string command).

- trimoutput.cpp scans through each output file produced by a SAT solver run and only retains information of interest.

- toexcel.cpp takes the information of interest and forms data table and from there to create table and figure for the project. 
