# Page-Replacement-Simulator

This repo contains the algorithms for page replacement. Page replacement is a memory management technique used in operating systems to manage the contents of the page table and ensure efficient use of physical memory. When a program needs to access a page that is not currently in physical memory (a page fault), the operating system must bring the required page from disk into memory. If the physical memory is full, the OS needs to decide which page to remove (replace) to make space for the new page. This decision is made based on a page replacement algorithm.

This code simulates and test three different page replacement algorithms like First in First out(FIFO), Least Recently Used(LRU) and Optimal.

Applying the above three algorithms using *sim_engine.h* and *vmsim.c* on the data generated via *vmgen.c*, we are able to compare the performance using the stats generated using *vmstats.c* to compare and analyse all the three algorithms.
