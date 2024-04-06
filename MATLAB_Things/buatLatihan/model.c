/* State equations. */

void compute_dx(double *dx, double *x, double *u, double **p){
    /* Retrieve model parameters. */

    double *F, *M, *C, *d, *A, *I, *m, *K;

    F = p[0]; /* Aerodynamic force coefficient. */
    M = p[1]; /* Aerodynamic momentum coefficient. */
    C = p[2]; /* Aerodynamic compensation factor. */
    d = p[3]; /* Body diameter. */
    A = p[4]; /* Body reference area. */
    I = p[5]; /* Moment of inertia, x-y-z. */
    m = p[6]; /* Mass. */
    K = p[7]; /* Feedback gain. */

    /* x[0]: Angular velocity around x-axis. */
    /* x[1]: Angular velocity around y-axis. */
    /* x[2]: Angular velocity around z-axis. */
    /* x[3]: Angle of attack. */
    /* x[4]: Angle of sideslip. */
    /* x[5]: Angle of sideslip. */
    /* x[6]: Angle of sideslip. */

    dx[0] = 1/I[0]*(d[0]*A[0]*(M[0]*x[4]+0.5*M[1]*d[0]*x[0]/u[4]+M[2]*u[0])*u[3]-(I[2]-I[1])*x[1]*x[2])+K[0]*(u[5]-x[0]);
    dx[1] = 1/I[1]*(d[0]*A[0]*(M[3]*x[3]+0.5*M[4]*d[0]*x[1]/u[4]+M[5]*u[1])*u[3]-(I[0]-I[2])*x[0]*x[2])+K[0]*(u[6]-x[1]);
    dx[2] = 1/I[2]*(d[0]*A[0]*(M[6]*x[4]+M[7]*x[3]*x[4]+0.5*M[8]*d[0]*x[2]/u[4]+M[9]*u[0]+M[10]*u[2])*u[3]-(I[1]-I[0])*x[0]*x[1])+K[0]*(u[7]-x[2]);
    dx[3] = (-A[0]*u[3]*(F[2]*x[3]+F[3]*u[1]))/(m[0]*u[4])-x[0]*x[4]+x[1]+K[0]*(u[8]/u[4]-x[3])+C[0]*pow(x[4],2);
    dx[4] = (-A[0]*u[3]*(F[0]*x[4]+F[1]*u[2]))/(m[0]*u[4])-x[2]+x[0]*x[3]+K[0]*(u[9]/u[4]-x[4]);
}

/* Output equations. */

void compute_y(double *y, double *x, double *u, double **p){
/* Retrieve model parameters. */

    double *F, *A, *m;

    F = p[0]; /* Aerodynamic force coefficient. */
    A = p[4]; /* Body reference area. */
    m = p[6]; /* Mass. */

    /* y[0]: Angular velocity around x-axis. */
    /* y[1]: Angular velocity around y-axis. */
    /* y[2]: Angular velocity around z-axis. */
    /* y[3]: Acceleration in y-direction. */
    /* y[4]: Acceleration in z-direction. */

    y[0] = x[0];
    y[1] = x[1];
    y[2] = x[2];
    y[3] = -A[0]*u[3]*(F[0]*x[4]+F[1]*u[2])/m[0];
    y[4] = -A[0]*u[3]*(F[2]*x[3]+F[3]*u[1])/m[0];
}