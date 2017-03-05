* SPICE FET model
.lib 'mos_tt.lib'
mfet1 2 5 3 2 pch w=10u l=2u
mfet2 2 6 5 2 pch w=10u l=2u
mfet3 2 3 4 2 pch w=10u l=2u
mfet4 2 0 6 2 pch w=10u l=2u
mfet5 0 4 2 2 pch w=10u l=2u
mfet6 1 5 3 1 nch w=6u l=2u
mfet7 1 6 5 1 nch w=6u l=2u
mfet8 1 3 4 1 nch w=6u l=2u
mfet9 1 0 6 1 nch w=6u l=2u
mfet10 0 4 1 1 nch w=6u l=2u
c1 1 6 0.0174pF
c2 1 5 0.0174pF
c3 0 1 0.0608pF
c4 1 3 0.0174pF
c5 1 4 0.0174pF
** Net name table **
*$ VO	0
*$ GND	1
*$ VDD	2
vs 2 1 5v
.ic v(0)=0V
.tran 1ns 100ns
.end

