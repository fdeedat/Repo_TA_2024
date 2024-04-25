#include "mex.h"
#include "math.h"

#define NY 3

/* State equations. */
void compute_dx(double *dx, double *x, double *u, double **p){
    /* Retrieve model parameters. */
    double *Ixx, *Iyy, *Izz, *Krx, *Kry, *Krz, *Brx, *Bry;

    Ixx = p[0]; 
    Iyy = p[1]; 
    Izz = p[2];
    Krx = p[3];
    Kry = p[4];
    Krz = p[5];
    Brx = p[6];
    Bry = p[7];

    dx[0] = x[3];
    dx[1] = x[4];
    dx[2] = x[5];
    dx[3] = ((Iyy-Izz)/Ixx)*x[4]*x[5]+u[0]/Ixx-Krx*x[3]/Ixx-Brx*x[0]/Ixx;
    dx[4] = ((Izz-Ixx)/Iyy)*x[3]*x[5]+u[1]/Iyy-Kry*x[4]/Iyy-Bry*x[1]/Iyy;
    dx[5] = ((Ixx-Iyy)/Izz)*x[3]*x[4]+u[2]/Izz-Krz*x[5]/Izz;
}

/* Output equations. */
void compute_y(double *y, double *x, double *u, double **p){
/* Retrieve model parameters. */

    /* y[0]: Angular velocity around x-axis. */
    /* y[1]: Angular velocity around y-axis. */
    /* y[2]: Angular velocity around z-axis. */

    y[0] = x[3];
    y[1] = x[4];
    y[2] = x[5];
}

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