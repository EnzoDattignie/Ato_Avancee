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
  double r6, r12;
  r6 = rsq * rsq * rsq;
  r12 = r6 * r6;
  uc = 4.0/pow(rcut,12) - 4.0/pow(rcut,6);
  *u = 4.0 * (1.0/r12 - 1.0/r6) - uc;
  *w = 24.0 * (2.0/r12 - 1.0/r6) / rsq;
}

/* Apply minimum image convention to a distance vector r. */
/* This function can also be used to fold a particle back  */
/* in the central cell during a simulation. However, it won't */
/* correctly fold back a particle from an arbitrary position. */
void pbc (int n, double r[], double box[]) {
  int i;
  for (i=0; i<n; ++i) {
    if (r[i] > box[i]/2.0) {
      // printf("r sup a demi boite");
      r[i] -= box[i];
    }
    else if (r[i] < -box[i]/2.0) {
      // printf("r inf a demi boite");
      r[i] += box[i];
    }
  }
}

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

void pos_center (int ndim, int n, double pos[],double center[]) {
  for (int i=0; i<ndim; i++) {
    center[i]=0;
  }
  for (int j=0; j<n; j++) {
    for (int i=0; i<1; i++) {
      center[i]+=pos[j*ndim+i];
    }
  }
  for (int i=0; i<ndim; i++) {
    center[i]=center[i]/n;
  }
  printf("Position du centre x = %f; y = %f; z = %f\n",center[0],center[1],center[2]);
}

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
      pbc(ndim, rij, box);
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
  for (i=0; i<n; i++)
    pbc(ndim, &(pos[i*ndim]), box);

  forces(ndim, n, rcut, box, pos, forc, epot,ListeVerlet);

  for (i=0; i<n; i++) 
    for (k=0; k<ndim; k++) 
      vel[i*ndim+k] += 0.5 * forc[i*ndim+k] / mass * dt;

}

/* Read a configuration in xyz format from file. */
/* Positions and velocities are stored in 1d arrays */
/* Return: box size, positions and velocities of particles */
void read_file (FILE *fp, int *npart, int *ndim, double **box, double **pos, double **vel) {
  int i, n, err;
  char a[256], b[256];
  double x, y, z, vx, vy, vz;
  err = fscanf(fp,"%d",&n);
  err = fscanf(fp, "%lf %lf %lf", &x, &y, &z);
  *ndim = 3;
  *npart = n;
  *pos = malloc((*ndim)*n*sizeof(double));
  *vel = malloc((*ndim)*n*sizeof(double));
  *box = malloc((*ndim)*sizeof(double));
  (*box)[0] = x;
  (*box)[1] = y;
  (*box)[2] = z;
  for (i=0; i<n; i++) {
    err = fscanf(fp, "%s %lf %lf %lf %lf %lf %lf", a, &x, &y, &z, &vx, &vy, &vz);
    (*pos)[i*(*ndim)]   = x;
    (*pos)[i*(*ndim)+1] = y;
    (*pos)[i*(*ndim)+2] = z;
    (*vel)[i*(*ndim)]   = vx;
    (*vel)[i*(*ndim)+1] = vy;
    (*vel)[i*(*ndim)+2] = vz;
  }
}

/* Dump some thermodynamic quantities to file */
void report (int what, FILE *fp, int ndim, int n, int steps, double pos[], double vel[], double epot) {
  double ekin;
  double center[3];
  pos_center(ndim,n,pos,center);
  if (what == 0) {
    fprintf(fp,"# %6s %14s %14s %14s %14s ","Steps", "Epot", "Temp", "Ekin", "Etot");
    for (int i = 0; i < ndim; i++) {
      fprintf(fp,"%13s%1d","Coord",i);
    }
    fprintf(fp,"\n");
  }
  else if (what == 1) {
    ekin = kinetic(ndim, n, vel);
    fprintf(fp, "%8d %14f %14f %14f %14f ", steps, epot, 2.0*ekin/(n*ndim), ekin, epot+ekin);
    for (int i = 0; i < ndim; i++) {
      fprintf(fp,"%14f",center[i]);
    }
    fprintf(fp,"\n");
  }
}

void ListeVerlet(int n, int ndim, double rverlet, double pos[], double box[], int Liste[]){
  double rij[ndim];
  for (int i = 0;i<n; i++) {
    for (int j = i+1; j < n; j++) {
      double rijsq = 0;
      for (int d = 0; d < ndim; d++) 
        rij[d] = pos[i*ndim+d]-pos[j*ndim+d];
        pbc(ndim, rij, box);
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

int main (int argc, char * argv[]) {
  int i, n, k, ndim, nsteps = 100;
  double *box, dt = 0.002, rc = 2.5, rverlet = 0.3+rc, epot;
  double *pos, *vel, *forc;
  FILE *file, *log;
  int *Liste;
  file = fopen("input_N4096.xyz","r");
  log  = fopen("output.log","w");
  /* Read input configuration and allocate arrays */
  read_file(file, &n, &ndim, &box, &pos, &vel);
  forc = malloc(n*ndim*sizeof(*forc));
  Liste = malloc(n*n*sizeof(*Liste));
  ListeVerlet(n,ndim, rverlet, pos,box,Liste);
  forces(ndim,n,rc,box,pos,forc,&epot,Liste);
  report(0,log,ndim,n,0,pos,vel,epot);
  /* Main MD loop */
  for (i=0; i<nsteps; i++) {
    evolve(ndim,n,dt,rc,box,pos,vel,forc,&epot,Liste);
    if (i % 10 == 0) {
      report(1,log,ndim,n,i,pos,vel,epot);}
      if (i % 20 == 0) {
      ListeVerlet(n,ndim, rverlet, pos,box,Liste);}
  }
  fclose(file);
  fclose(log);
}
