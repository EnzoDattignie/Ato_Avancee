/* Simple (and inefficient!) molecular dynamics code for a Lennard-Jones system. */
/* The code is only meant for pedagogical purposes, not for production. */
/* Author: Daniele Coslovich (daniele.coslovich@umontpellier.fr) */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Evaluate the potential energy and the virial contribution  */
/* using the cut and shifted Lennard-Jones potential */
void potential (double rcut, double rsq, double *u, double *w) {
  double uc;
  double r6, r12,rcut2i,rcut6i,rcut12i;
  rcut2i = 1/(rcut*rcut);
  rcut6i = rcut2i*rcut2i*rcut2i;
  rcut12i = rcut6i*rcut6i;
  r6 = rsq * rsq * rsq;
  r12 = r6 * r6;

  uc = 4.0*rcut12i - 4.0*rcut6i;
  *u = 4.0 * (1.0/r12 - 1.0/r6) - uc;
  *w = 24.0 * (2.0/r12 - 1.0/r6) / rsq;
}

/* Apply minimum image convention to a distance vector r. */
/* This function can also be used to fold a particle back  */
/* in the central cell during a simulation. However, it won't */
/* correctly fold back a particle from an arbitrary position. */
// void pbc (int n, double r[], double box[]) {
//   int i;
//   for (i=0; i<n; ++i) {
//     if (r[i] > box[i]/2.0) {
//       // printf("r sup a demi boite");
//       r[i] -= box[i];
//     }
//     else if (r[i] < -box[i]/2.0) {
//       // printf("r inf a demi boite");
//       r[i] += box[i];
//     }
//   }
// }

/* Evaluate the kinetic energy from the particles' velocities */
double kinetic (int ndim, int n, double vel[]) {
  int i, j;
  double ekin = 0.0;
  for (j=0; j<n; j++) {
    for (i=0; i<ndim; i++) {
      ekin += pow(vel[j*ndim+i],2);
    }
  }
  ekin *= 0.5;
  return ekin;
}

void pos_center (int ndim, int n, double pos[],double center[],char ListAB[],int npas) {
  for (int i=0; i<ndim*2; i++) {
    center[i]=0;
  }
  int AB = 0;
  int nA = 0;
  int nB = 0;
  for (int j=0; j<n; j++) {
    if(ListAB[j]=='A') {
        AB = 0;
        nA ++;
    } 
    if(ListAB[j]=='B') {
      AB = 1;
      nB ++;
    }
    for (int i=0; i<ndim; i++) {
      
      center[i+AB*ndim]+=pos[j*ndim+i];
    }
  }
  for (int i=0; i<ndim; i++) {
    center[i]=center[i]/nA;
    center[i+ndim]=center[i+ndim]/nB;
  }
  printf("Pas = %d \nPosition du centre A x = %f; y = %f; z = %f\nPosition du centre B x = %f; y = %f; z = %f\n",npas,center[0],center[1],center[2],center[3],center[4],center[5]);
}

void Rg_calc(int ndim, int n, double pos[],double center[],char ListAB[], double Rg[]) {
  double sommeA = 0;
  double sommeB = 0;
  int nA = 0, nB = 0;
  for (int j=0; j<n; j++) {
    if (ListAB[j] == 'A') {
    for (int d = 0; d < ndim; d++) {
      sommeA += (pos[j*ndim+d] - center[d])*(pos[j*ndim+d] - center[d]);
    }
      nA ++;
    }
    if (ListAB[j] == 'B') {
    for (int d = 0; d < ndim; d++) {
      sommeB += (pos[j*ndim+d] - center[d])*(pos[j*ndim+d] - center[d+ndim]);
    }
      nB ++;
    }
}
  Rg[0] = sqrt(sommeA)/nA;
  Rg[1] = sqrt(sommeB)/nB;
}

// void Rg_calc (int ndim, int n, double pos[], double center[], double *Rg) {
//   double somme = 0;
//   for (int j=0; j<n; j++) {
//     for (int d = 0; d < ndim; d++) {
//       somme += (pos[j*ndim+d] - center[d])*(pos[j*ndim+d] - center[d]);
//     }
//   }
//   *Rg = sqrt(somme)/n;
// }

/* Evaluate the potential energy and the forces between particles */
void forces ( int ndim, int n, double rcut, double box[], double pos[],
		double forc[], double *epot, int ListeVerlet[n*n]) {
  double rij[ndim], rijsq, uij, wij;
  int i, j, k;
  *epot = 0.0;
  for (i=0; i<n*ndim; i++) 
    forc[i] = 0.0;
  for (i=0; i<n; i++) {
    for (j=i+1; j<n; j++) {
      if (ListeVerlet[i*n+j]==1) {
      for (k=0; k<ndim; k++) 
	      rij[k] = pos[ndim*i+k] - pos[ndim*j+k];
      // pbc(ndim, rij, box);
      rijsq = 0.0;
      for (k=0; k<ndim; k++) 
	      rijsq += pow(rij[k],2);
      if (rijsq < pow(rcut,2)) {
	potential(rcut, rijsq, &uij, &wij);
	*epot += uij;
	for (k=0; k<ndim; k++) {
	  forc[i*ndim+k] += wij * rij[k];
	  forc[j*ndim+k] -= wij * rij[k];
	}}
      }
    }
  }
}

/* Integration step using the velocity-Verlet algorithm */
void evolve (int ndim, int n, double dt, double rcut, double box[],
		double pos[], double vel[], double forc[], double *epot, int ListeVerlet[]) {
  int i, j, k;
  double mass = 1.0;
  
  for (i=0; i<n; i++)
    for (k=0; k<ndim; k++) {
      pos[i*ndim+k] += vel[i*ndim+k] * dt + 0.5 * forc[i*ndim+k] / mass * pow(dt,2);
      vel[i*ndim+k] += 0.5 * forc[i*ndim+k] / mass * dt;
    }
  // for (i=0; i<n; i++)
  //   pbc(ndim, &(pos[i*ndim]), box);

  forces(ndim, n, rcut, box, pos, forc, epot,ListeVerlet);

  for (i=0; i<n; i++) 
    for (k=0; k<ndim; k++) 
      vel[i*ndim+k] += 0.5 * forc[i*ndim+k] / mass * dt;

}

/* Read a configuration in xyz format from file. */
/* Positions and velocities are stored in 1d arrays */
/* Return: box size, positions and velocities of particles */
void read_file (FILE *fp, int *npart, int *ndim, double **box, double **pos, double **vel, char **AB) {
  int i, n, err;
  char a[256], b[256];
  double x, y, z, vx, vy, vz;
  double dilatation = 1.0;
  double speed = 1.0;
  err = fscanf(fp,"%d",&n);
  err = fscanf(fp, "%lf %lf %lf", &x, &y, &z);
  *ndim = 3;
  *npart = n;
  *pos = malloc((*ndim)*n*sizeof(double));
  *vel = malloc((*ndim)*n*sizeof(double));
  *box = malloc((*ndim)*sizeof(double));
  *AB = malloc((n)*sizeof(*AB));
  (*box)[0] = x;
  (*box)[1] = y;
  (*box)[2] = z;
  for (i=0; i<n; i++) {
    err = fscanf(fp, "%s %lf %lf %lf %lf %lf %lf", a, &x, &y, &z, &vx, &vy, &vz);
    (*pos)[i*(*ndim)]   = x*dilatation;
    (*pos)[i*(*ndim)+1] = y*dilatation;
    (*pos)[i*(*ndim)+2] = z*dilatation;
    (*vel)[i*(*ndim)]   = vx*speed;
    (*vel)[i*(*ndim)+1] = vy*speed;
    (*vel)[i*(*ndim)+2] = vz*speed;
    (*AB)[i] = a[0];
  }
}

/* Dump some thermodynamic quantities to file */
void report (int what, FILE *fp, int ndim, int n, int steps, double pos[], double vel[], double epot, char AB[],int npas, double Rg[]) {
  double ekin;
  double center[ndim*2];
  pos_center(ndim,n,pos,center,AB,npas);
  Rg_calc(ndim,n,pos,center,AB,Rg);
  if (what == 0) {
    fprintf(fp,"# %6s %14s %14s %14s %14s ","Steps", "Epot", "Temp", "Ekin", "Etot");
    fprintf(fp,"%14s","RgA");
    for (int i = 0; i < ndim; i++) {
      fprintf(fp,"%12s%1d%1s","Coord",i,"A");
    }
    fprintf(fp,"%14s","RgB");
    for (int i = 0; i < ndim; i++) {
      fprintf(fp,"%12s%1d%1s","Coord",i,"B");
    }
    fprintf(fp,"\n");
  }
  else if (what == 1) {
    ekin = kinetic(ndim, n, vel);
    fprintf(fp, "%8d %14f %14f %14f %14f ", steps, epot, 2.0*ekin/(n*ndim), ekin, epot+ekin);
    for (int i = 0; i < ndim*2; i++) {
      if (i == 0) {
        fprintf(fp,"%14f",Rg[0]);
      }
      if (i == 3) {
        fprintf(fp,"%14f",Rg[1]);
      }
      fprintf(fp,"%14f",center[i]);
    }
    fprintf(fp,"\n");
  }
}

// void report (int what, FILE *fp, int ndim, int n, int steps, double pos[], double vel[], double epot, char AB[],int npas, double Rg) {
//   double ekin;
//   double center[ndim*2];
//   pos_center(ndim,n,pos,center,AB,npas);
//   Rg_calc (ndim,n,pos,center,&Rg);
//   if (what == 0) {
//     fprintf(fp,"# %6s %14s %14s %14s %14s ","Steps", "Epot", "Temp", "Ekin", "Etot");
//     fprintf(fp,"%14s","RgA");
//     for (int i = 0; i < ndim; i++) {
//       fprintf(fp,"%12s%1d%1s","Coord",i,"A");
//     }
//     // fprintf(fp,"%14s","RgB");
//     // for (int i = 0; i < ndim; i++) {
//     //   fprintf(fp,"%12s%1d%1s","Coord",i,"B");
//     // }
//     fprintf(fp,"\n");
//   }
//   else if (what == 1) {
//     ekin = kinetic(ndim, n, vel);
//     fprintf(fp, "%8d %14f %14f %14f %14f ", steps, epot, 2.0*ekin/(n*ndim), ekin, epot+ekin);
//     for (int i = 0; i < ndim; i++) {
//       if (i == 0) {
//         fprintf(fp,"%14f",Rg);
//       }
//       // if (i == 3) {
//       //   fprintf(fp,"%14f",0.);
//       // }
//       fprintf(fp,"%14f",center[i]);
//     }
//     fprintf(fp,"\n");
//   }
// }

void ListeVerlet(int n, int ndim, double rverlet, double pos[], double box[], int Liste[]){
  double rij[ndim];
  for (int i = 0;i<n; i++) {
    for (int j = i+1; j < n; j++) {
      double rijsq = 0;
      for (int d = 0; d < ndim; d++) 
        rij[d] = pos[i*ndim+d]-pos[j*ndim+d];
        // pbc(ndim, rij, box);
      for (int d = 0; d < ndim; d++) 
        rijsq += rij[d]*rij[d];
      if (rijsq < rverlet) {
        Liste[i*n+j] = 1;
        // printf("Oui part %d %d\n",i,j);
      } else {
        Liste[i*n+j] = 0;
        // printf("Non part %d %d\n",i,j);
      }
    }
  }
}

void write_xyz (FILE *fp, int ndim, int n, double pos[]) {
  int i, j;
  fprintf(fp, "%d\n", n);
  fprintf(fp, "\n");
  // for (j=0; j<n; j++) {
  //   fprintf(fp, "A %f %f %f\n",  pos[j*ndim],  pos[j*ndim+1],  pos[j*ndim+2]);
  // }
  for (j=0; j<n/2; j++) {
    fprintf(fp, "A %f %f %f\n",  pos[j*ndim],  pos[j*ndim+1],  pos[j*ndim+2]);
  }
  for (j=n/2; j<n; j++) {
    fprintf(fp, "B %f %f %f\n",  pos[j*ndim],  pos[j*ndim+1],  pos[j*ndim+2]);
  }
}

int main (int argc, char * argv[]) {
  int i, n, k, ndim, nsteps = 20000;
  char *AB;
  double *box, dt = 0.002, rc = 2.5, rverlet = 0.3+rc, epot;
  double *pos, *vel, *forc, *Rg;
  FILE *file, *log, *write;
  int *Liste;
  write = fopen("res/Pos_Collision.xyz","w");
  file = fopen("nano_A_B.xyz","r");
  log  = fopen("res/Meas_Collision.log","w");
  /* Read input configuration and allocate arrays */
  read_file(file, &n, &ndim, &box, &pos, &vel, &AB);
  forc = malloc(n*ndim*sizeof(*forc));
  Liste = malloc(n*n*sizeof(*Liste));
  Rg = malloc(2*sizeof(*Rg));
  ListeVerlet(n,ndim, rverlet, pos,box,Liste);
  forces(ndim,n,rc,box,pos,forc,&epot,Liste);
  report(0,log,ndim,n,0,pos,vel,epot,AB,0,Rg);
  /* Main MD loop */
  for (i=0; i<nsteps; i++) {
    evolve(ndim,n,dt,rc,box,pos,vel,forc,&epot,Liste);
    if (i % 10 == 0) {
      
      report(1,log,ndim,n,i,pos,vel,epot,AB,i,Rg);}
      if (i % 20 == 0) {
      ListeVerlet(n,ndim, rverlet, pos,box,Liste);}
      if (i % 50 == 0) {
      write_xyz(write,ndim,n,pos);
      }
  }
  fclose(file);
  fclose(log);
}
