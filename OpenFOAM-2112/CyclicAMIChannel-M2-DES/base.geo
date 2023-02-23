dx = 0.06;

originx = 1.0;
originy = -4.0;
originz = -0.5;

lx = 5;
ly = 8.0;
lz = 4.5 - originz;

Point(1) = {originx, originy, originz};

Extrude {0, ly, 0} {
  Point{1}; Layers{ly/dx}; Recombine;
}

Extrude {lx, 0, -0.05} {
  Line{1}; Layers{lx/dx}; Recombine;
}

Extrude {0, 0, lz} {
  Surface{5}; Layers{lz/dx}; Recombine;
}

Coherence;

Physical Surface("inlet") = {14};
Physical Surface("outlet") = {22};
Physical Surface("atmosphere") = {18};
Physical Surface("sides") = {5,26,27};
Physical Volume(135) = {1};
Coherence;
