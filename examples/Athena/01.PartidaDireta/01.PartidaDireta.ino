/**********************************************************************

  LADDER
  
      I0    I1          Q0
  |---| |-+-|/|---------( )---|
  |       |                   |
  |   Q0  |                   |
  |---| |-+                   |
  |                           |
  |   Q0                Q1    |
  |---| |---------------( )---|
  |                           |
  |   Q0                Q2    |
  |---|/|---------------( )---| 
  
************************************************************************/


programa
inicio

  Q0 = ( (na I0) paralelo (na Q0) ) serie ( nf I1 );

  Q1 = (na Q0);

  Q2 = (nf Q0);

fim
