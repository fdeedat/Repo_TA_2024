/*   Copyright 2005-2006 The MathWorks, Inc. */

/* Include libraries. */
#include "mex.h"
#include "math.h"
#define M_PI 3.14159265358979323846

/* Specify the number of outputs here. */
#define NY 3

/* State equations. */
void compute_dx(
    double *dx,  /* Vector of state derivatives (length nx). */
    double t,    /* Time t (scalar). */
    double *x,   /* State vector (length nx). */
    double *u,   /* Input vector (length nu). */
    double **p,  /* p[j] points to the j-th estimated model parameters (a double array). */
    const mxArray *auxvar  /* Cell array of additional data. */
   )
{

    double *Ixx, *Iyy, *Izz, *Krx, *Kry, *Krz, *d, *ct, *cm, *Jr, *Brx, *Bry;

    Ixx = p[0]; 
    Iyy = p[1]; 
    Izz = p[2];
    Krx = p[3];
    Kry = p[4];
    Krz = p[5];
    // Brx = p[6];
    // Bry = p[7];
    // regM = p[12];
    // regC = p[13];
    // 
    // w1 = regM[0]*u[0]+regC[0];
    // w2 = regM[0]*u[1]+regC[0];
    // w3 = regM[0]*u[2]+regC[0];
    // w4 = regM[0]*u[3]+regC[0];

    dx[0] = x[3];
    dx[1] = x[4];
    dx[2] = x[5];
    dx[3] = ((Iyy[0]-Izz[0])/Ixx[0])*dx[1]*dx[2]+ (u[0])/Ixx[0]- Krx[0]*(dx[0]/Ixx[0]);//- Brx[0]*x[0]/Ixx[0];
    dx[4] = ((Izz[0]-Ixx[0])/Iyy[0])*dx[0]*dx[2]+ (u[1])/Iyy[0]- Kry[0]*(dx[1]/Iyy[0]);//- Bry[0]*x[1]/Iyy[0];
    dx[5] = ((Ixx[0]-Iyy[0])/Izz[0])*dx[1]*dx[0]+ (u[2])/Izz[0]- Krz[0]*x[5]/Izz[0];
}

/* Output equations. */
void compute_y(
    double *y,   /* Vector of outputs (length NY). */
    double t,    /* Time t (scalar). */
    double *x,   /* State vector (length nx). */
    double *u,   /* Input vector (length nu). */
    double **p,  /* p[j] points to the j-th estimated model parameters (a double array). */
    const mxArray *auxvar  /* Cell array of additional data. */
   )
{
    /*
      Define the output equation y = h(t, x, u, p[0],..., p[np-1], auvar)
      in the body of this function.
    */
    
    /*
      Accessing the contents of auxvar: see the discussion in compute_dx.
    */
    
    /* Example code from ODE function for DCMOTOR example
      used in idnlgreydemo1 (dcmotor_c.c) follows.
    */
    // y[0] = x[0]*180/M_PI;
    // y[1] = x[1]*180/M_PI;
    // y[2] = x[2]*180/M_PI;
    y[0] = x[3];
    y[1] = x[4];
    y[2] = x[5];
}



/*----------------------------------------------------------------------- *
   DO NOT MODIFY THE CODE BELOW UNLESS YOU NEED TO PASS ADDITIONAL
   INFORMATION TO COMPUTE_DX AND COMPUTE_Y
 
   To add extra arguments to compute_dx and compute_y (e.g., size
   information), modify the definitions above and calls below.
 *-----------------------------------------------------------------------*/

void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    /* Declaration of input and output arguments. */
    double *x, *u, **p, *dx, *y, *t;
    int     i, np, nu, nx;
    const mxArray *auxvar = NULL; /* Cell array of additional data. */
    
    if (nrhs < 3) {
        mexErrMsgIdAndTxt("IDNLGREY:ODE_FILE:InvalidSyntax",
        "At least 3 inputs expected (t, u, x).");
    }
    
    /* Determine if auxiliary variables were passed as last input.  */
    if ((nrhs > 3) && (mxIsCell(prhs[nrhs-1]))) {
        /* Auxiliary variables were passed as input. */
        auxvar = prhs[nrhs-1];
        np = nrhs - 4; /* Number of parameters (could be 0). */
    } else {
        /* Auxiliary variables were not passed. */
        np = nrhs - 3; /* Number of parameters. */
    }
    
    /* Determine number of inputs and states. */
    nx = mxGetNumberOfElements(prhs[1]); /* Number of states. */
    nu = mxGetNumberOfElements(prhs[2]); /* Number of inputs. */
    
    /* Obtain double data pointers from mxArrays. */
    t = mxGetPr(prhs[0]);  /* Current time value (scalar). */
    x = mxGetPr(prhs[1]);  /* States at time t. */
    u = mxGetPr(prhs[2]);  /* Inputs at time t. */
    
    p = mxCalloc(np, sizeof(double*));
    for (i = 0; i < np; i++) {
        p[i] = mxGetPr(prhs[3+i]); /* Parameter arrays. */
    }
    
    /* Create matrix for the return arguments. */
    plhs[0] = mxCreateDoubleMatrix(nx, 1, mxREAL);
    plhs[1] = mxCreateDoubleMatrix(NY, 1, mxREAL);
    dx      = mxGetPr(plhs[0]); /* State derivative values. */
    y       = mxGetPr(plhs[1]); /* Output values. */
    
    /*
      Call the state and output update functions.
      
      Note: You may also pass other inputs that you might need,
      such as number of states (nx) and number of parameters (np).
      You may also omit unused inputs (such as auxvar).
      
      For example, you may want to use orders nx and nu, but not time (t)
      or auxiliary data (auxvar). You may write these functions as:
          compute_dx(dx, nx, nu, x, u, p);
          compute_y(y, nx, nu, x, u, p);
    */
    
    /* Call function for state derivative update. */
    compute_dx(dx, t[0], x, u, p, auxvar);
    
    /* Call function for output update. */
    compute_y(y, t[0], x, u, p, auxvar);
    
    /* Clean up. */
    mxFree(p);
}
