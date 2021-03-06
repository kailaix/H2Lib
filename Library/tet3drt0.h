
/* ------------------------------------------------------------
 * This is the file "tet3drt0.h" of the H2Lib package.
 * All rights reserved, Nadine Albrecht 2015
 * ------------------------------------------------------------ */

/** @file tet3drt0.h
 *  @author Nadine Albrecht*/

#ifndef TET3DRT0_H
#define TET3DRT0_H

/** @defgroup tet3drt0 tet3drt0
 * @brief Lowest order Raviart-Thomas space on a three-dimensional tetrahedral mesh.
 * 
 * E.g., this space is useful to discretize darcy's flow(Raviart-Thomas) and
 * conservation of mass (piecewise constant functions), this leads to a 
 * saddle-point problem:
 *  @f[ \begin{pmatrix} A & B^T\\ B & \end{pmatrix}
 *      \begin{pmatrix} x_1\\ x_2 \end{pmatrix}
 *    = \begin{pmatrix} b_D\\ b_f \end{pmatrix} @f]
 * @{ */

/** @brief Representation of a trial space with Raviart-Thomas
 *  edge basis functions on a three-dimensional tetrahedral mesh. */
typedef struct _tet3drt0 tet3drt0;

/** @brief Pointer to @ref tet3drt0 object. */
typedef tet3drt0 *ptet3drt0;

/** @brief Pointer to a constant @ref tet3drt0 object.*/
typedef const tet3drt0 *pctet3drt0;

#include "sparsematrix.h"
#include "tet3d.h"
#include "clustergeometry.h"

/* ------------------------------------------------------------
   Edge-elements for a tetrahedral mesh
   ------------------------------------------------------------ */

/** @brief Representation of a trial space with lowest order
 *  Raviart-Thomas basis functions on a three-dimensional tetrahedral mesh.
 *
 *  Since the mesh itself is represented by a @ref tet3d object,
 *  we only have to keep track of which edges are degrees of
 *  freedom and provide them with consecutive indices for the
 *  algebraic functions.
 *
 *  The remaining edges are also provided with consecutive
 *  indices, allowing us to construct <em>interaction matrices</em>
 *  that describe how non-zero values in the fixed edges influence
 *  the right-hand side of a variational equation.
 *  This mechanism is useful, e.g., for handling inhomogeneous Dirichlet
 *  boundary conditions. 
 */
struct _tet3drt0
{
  /** @brief Triangular mesh, represented by @ref tet3d object.*/
  pctet3d t3;  
  
  /** @brief Number of degrees of freedom.*/
  uint ndof;    
  
  /** @brief Number of fixed faces*/
  uint nfix;      
  
  /** @brief Determines whether an face is a degree or freedom or fixed.
   *
   * After the call of @ref new_tet3drt0 : 0 inner face, 1 boundary face.
   * Use 1 Dirichlet face and 2  Neumann face for mixed boundary conditions*/
  uint *is_dof; 
  
  /** @brief Consecutive indices for all degrees of freedom and all fixed faces.*/
  uint *idx2dof; 
};

/** @brief Create a @ref tet3drt0 object using a @ref tet3d mesh.
 *
 *  The boundary flags <tt>gr->eb</tt> are used to decide whether
 *  an edge corresponds to a degree of freedom or is fixed.
 *
 *  @param gr Mesh
 *  @returns @ref tet3drt0 object matching <tt>gr</tt>. */
HEADER_PREFIX ptet3drt0
new_tet3drt0(pctet3d gr);

/** @brief Update the numbers of degrees of freedoms and fixed faces after 
 *  mixed boundary conditions were set.
 *
 * Set the mixed boundary conditions in another function. Then the call
 * of this functions updates the numbers and the numbering of degrees of freedoms 
 * and fixed faces.
 * 
 * @param rt0 This structure is updated.*/
HEADER_PREFIX void 
update_tet3drt0(ptet3drt0 rt0);

/** @brief Delete a @ref tet3drt0 object.
 *
 *  @param rt Object to be deleted. */
HEADER_PREFIX void
del_tet3drt0(ptet3drt0 rt);

/** @brief Create a @ref sparsematrix with a sparsity pattern matching
 *  the lowest order Raviart-Thomas functions and representing the upper
 *  left block of the saddle-point problem.
 *
 *  Creates a sparse matrix matching the Raviart-Thomas functions:
 *  if the supports of basis functions @f$\varphi_i@f$ and
 *  @f$\varphi_j@f$ share at least one tetrahedron, the entry
 *  @f$a_{ij}@f$ appears in the graph of the matrix.
 *
 *  Here, both @f$i@f$ and @f$j@f$ refer to degrees of freedom,
 *  i.e., there indices are between <tt>0</tt> and <tt>ndof-1</tt>.
 *
 *  @param dc @ref tet3drt0 object describing the space.
 *  @returns Sparse matrix with <tt>dc->ndof</tt> rows and columns. */
HEADER_PREFIX psparsematrix
build_tet3drt0_A_sparsematrix(pctet3drt0 dc);

/** @brief Create a @ref sparsematrix with a sparsity pattern matching
 *  the lowest order Raviart-Thomas functions for the flux and piecewise-
 *  constant functions for the pressure representing the lower left block
 *  of the saddle-point problem.
 *
 *  Creates a sparse matrix matching the Raviart-Thomas functions for
 *  the flux and piecewise-constant functions for the pressure:
 *  if the supports of basis functions @f$\varphi_i@f$ (pressure) and
 *  @f$\varphi_j@f$ (flux) share at least one tetrahedron, the entry
 *  @f$a_{ij}@f$ appears in the graph of the matrix.
 *
 *  @f$i@f$ refers to the number of triangles in the mesh, i.e., the indices 
 *  are between <tt>0</tt> and <tt>dc->t2->triangles-1</tt> and 
 *  @f$j@f$ refers to degrees of freedom,i.e., the indices are between 
 *  <tt>0</tt> and <tt>ndof-1</tt>.
 *
 *  @param dc @ref tet3drt0 object describing the space.
 *  @returns Sparse matrix with <tt>dc->t3->tetrahedra </tt>  rows 
 *         and<tt>dc->ndof</tt> columns. */
HEADER_PREFIX psparsematrix
build_tet3drt0_B_sparsematrix(pctet3drt0 dc);

/** @brief Create a @ref sparsematrix with a sparsity pattern matching
 *  the lowest order Raviart-Thomas functions and representing the upper
 *  left block of the saddle-point problem representing the interaction matrix.
 *
 *  Creates a sparse matrix matching the Raviart-Thomas functions:
 *  if the supports of basis functions @f$\varphi_i@f$ and
 *  @f$\varphi_j@f$ share one tetrahedron, the entry
 *  @f$a_{ij}@f$ appears in the graph of the matrix.
 *
 *  Here, only @f$i@f$ refers to a degree of freedom, while 
 *  @f$j@f$ is the index of a fixed edge, i.e. has to be between
 *  <tt>0</tt> and <tt>nfix-1</tt>.
 * 
 *  @param dc @ref tet3drt0 object describing the space.
 *  @returns Sparse matrix with <tt>dc->ndof</tt> rows and
 *    <tt>dc->nfix</tt> columns. */
HEADER_PREFIX psparsematrix
build_tet3drt0_A_interaction_sparsematrix(pctet3drt0 dc);


/** @brief Create a @ref sparsematrix with a sparsity pattern matching
 *  the lowest order Raviart-Thomas functions for the flux and piecewise-
 *  constant functions for the pressure representing the lower left block
 *  of the saddle-point problem representing the interaction matrix.
 *
 *  Creates a sparse matrix matching the Raviart-Thomas functions for
 *  the flux and piecewise-constant functions for the pressure:
 *  if the supports of basis functions @f$\varphi_i@f$ (pressure) and
 *  @f$\varphi_j@f$ (flux) share at least one tetrahedron, the entry
 *  @f$a_{ij}@f$ appears in the graph of the matrix.
 *
 *  @f$i@f$ refers to the number of tetrahedra in the mesh, i.e., the indices 
 *  are between <tt>0</tt> and <tt>dc->t3->tetrahedra-1</tt> and 
 *  @f$j@f$ is the index of a fixed face, i.e. has to be between
 *  <tt>0</tt> and <tt>nfix-1</tt>.
 *
 *  @param dc @ref tri2drt0 object describing the space.
 *  @returns Sparse matrix with <tt>dc->t3->tetrahedra </tt>  rows 
 *         and<tt>dc->nfix</tt> columns. */
HEADER_PREFIX psparsematrix
build_tet3drt0_B_interaction_sparsematrix(pctet3drt0 dc);

/** @brief Assemble the upper left block of the system matrix.
 *
 *  Element matrices for all triangles are computed and added
 *  to the corresponding entries in <tt>A</tt> and <tt>Af</tt>.
 *
 *  @param dc @ref tet3drt0 object describing the trial space.
 *  @param A Target matrix for degrees of freedom.
 *  @param Af Target matrix for interactions between fixed vertices
 *    and degrees of freedom. 
 *  @param K Vector of length <tt>dc->t3->tetrahedra</tt> filled with a
              (constant) permeability for each element*/
HEADER_PREFIX void
assemble_tet3drt0_darcy_A_sparsematrix(pctet3drt0 dc, psparsematrix A, psparsematrix Af, pavector K);

/** @brief Assemble the lower left block of the system matrix.
 *
 *  Element matrices for all triangles are computed and added
 *  to the corresponding entries in <tt>A</tt> and <tt>Af</tt>.
 *
 *  @param dc @ref tet3drt0 object describing the trial space.
 *  @param A Target matrix for degrees of freedom.
 *  @param Af Target matrix for interactions between fixed vertices
 *    and degrees of freedom. */
HEADER_PREFIX void
assemble_tet3drt0_darcy_B_sparsematrix(pctet3drt0 dc, psparsematrix A, psparsematrix Af);

/** @brief Discretize Dirichlet boundary values.
 *
 *  For each Dirichlet face, the function @f$f@f$ is evaluated with the face 
 *  midpoint rule and the result is written to the corresponding entry in the 
 *  result vector.
 *  for each non boundary face the corresponding entry is zero.
 *
 *  @param dc @ref tet3drt0 object describing the trial space.
 *  @param f Dirichlet boundary values.
 *  @param fdata Additional data for <tt>f</tt>.
 *  @param d Target vector of dimension <tt>dc->nfix</tt>. */
HEADER_PREFIX void
assemble_tet3drt0_b_D_avector(pctet3drt0 dc,
		  field (*f)(const real *e, void *fdata), void *fdata,
		  pavector d);


/** @brief Discretize an @f$L^2@f$ -functional.
 *
 *  For each tetrahedron the entry of @f$fv_i@f$ is computed by applying
 *  the face-midpoint quadrature. 
 *  Since @f$fv@f$ is cleared before this step, the result is given by
 *  @f$fv_i = \int_{T_i} f(x) \,dx@f$.
 *
 *  @param dc @ref tet3drt0 object describing the trial space.
 *  @param f Right-hand side function of the conservation of mass.
 *  @param fdata Additional data for <tt>f</tt>.
 *  @param fv Target vector of dimension <tt>dc->t2->triangles</tt>. */
HEADER_PREFIX void
assemble_tet3drt0_b_f_avector(ptet3drt0 dc,
                   field (*f)(const real *x, void *fdata), void *fdata,
                   pavector fv);

/** @brief Discretize Neumann Boundary values.
 * 
 *  Subtracting @f$A_f g@f$ resp. @f$Bf g@f$ from the right-hand side of our 
 *  equation, where @f$A_f@f$ resp. @f$Bf g@f$ is the interaction matrix, yields
 *  the right-hand side of the problem with Neumann boundary conditions.
 * 
 *  @param dc @ref tet3drt0 object describing the trial space.
 *  @param f Neumann Boundary values.
 *  @param data Additional data for <tt>f</tt>.
 *  @param g Target vector of dimension <tt>dc->nfix</tt>. */
void assemble_tet3drt0_g_N_avector(ptet3drt0 dc, 
				   field (*f)(const uint *e, void *data), void *data,
				   pavector g);

/** @brief Compute the @f$L^2@f$-norm of the discretization error for the 
 *         pressure using the centroid rule.
 *
 *  Compare the pressure function <tt>f</tt> to the discrete function for the 
 *  pressure described by the vector <tt>x2</tt>.
 *  Measure the difference in the @f$L^2@f$-norm using the midpoint rule for 
 *  approximation of the integral.
 *
 *  @param dc @ref tet3drt0 object describing the trial space.
 *  @param f Function.
 *  @param fdata Additional data for <tt>f</tt>.
 *  @param x2 Coefficients of discrete function.
 *  @returns @f$L^2@f$-norm of discretization error of the pressure. */
HEADER_PREFIX real
norml2_pressure_centroid_tet3drt0(pctet3drt0 dc,
	       field(*f) (const real * x, void *fdata), void *fdata,
	       pcavector x2);

/** @brief Compute the @f$L^2@f$-norm of the discretization error for the 
 *         pressure using the centroid rule.
 *
 *  Compare the pressure function <tt>f</tt> to the discrete function for the 
 *  pressure described by the vector <tt>x2</tt>.
 *  Measure the difference in the @f$L^2@f$-norm using the centroid rule for 
 *  approximation of the integral.
 *
 *  @param dc @ref tet3drt0 object describing the trial space.
 *  @param f Function.
 *  @param fdata Additional data for <tt>f</tt>.
 *  @param x2 Coefficients of discrete function.
 *  @returns @f$L^2@f$-norm of discretization error of the pressure. */
HEADER_PREFIX real
norml2_pressure_facemidpoint_tet3drt0(pctet3drt0 dc,
	       field(*f) (const real * x, void *fdata), void *fdata, pcavector x2);

/** @brief Compute the @f$L^2@f$-norm of the discretization error for the 
 *         flux using the centroid rule.
 *
 *  Compare the function <tt>f</tt> for the flux to the discrete function for the 
 *  flux described by the vector <tt>x1</tt> (for the degrees of freedom) and 
 *  <tt>g</tt> (for the fixed Neumann edges).
 *  Measure the difference in the @f$L^2@f$-norm using the centroid rule for 
 *  approximation of the integral.
 *
 *  @param dc @ref tet3drt0 object describing the trial space.
 *  @param f Function.
 *  @param fdata Additional data for <tt>f</tt>.
 *  @param x1 Coefficients of the discrete function.
 *  @param g Coefficients of fixed parts of the discrete function.
 *  @returns @f$L^2@f$-norm of the discretization error of the flux. */
HEADER_PREFIX real
norml2_flux_centroid_tet3drt0(pctet3drt0 dc,
	       void (*q) (const real * x, void *fdata, pavector v), void *fdata,
	       pcavector x1, pcavector g);

/** @brief Compute the @f$L^2@f$-norm of the discretization error for the 
 *         flux using the face midpoint rule.
 *
 *  Compare the function <tt>f</tt> for the flux to the discrete function for the 
 *  flux described by the vector <tt>x1</tt> (for the degrees of freedom) and 
 *  <tt>g</tt> (for the fixed Neumann edges).
 *  Measure the difference in the @f$L^2@f$-norm using the face midpoint rule for 
 *  approximation of the integral.
 *
 *  @param dc @ref tri2drt0 object describing the trial space.
 *  @param f Function.
 *  @param fdata Additional data for <tt>f</tt>.
 *  @param x1 Coefficients of the discrete function.
 *  @param g Coefficients of fixed parts of the discrete function.
 *  @returns @f$L^2@f$-norm of the discretization error of the flux. */
HEADER_PREFIX real
norml2_flux_facemidpoint_tet3drt0(pctet3drt0 dc,
	       void (*q) (const real * x, void *fdata, pavector v), void *fdata,
	       pcavector x1, pcavector g);


/* ------------------------------------------------------------
   Clustergeometry
   ------------------------------------------------------------ */

/** @brief Create a @ref clustergeometry object for the clustering ofthe degrees
 *  of freedom (edges).
 * 
 * Create a @ref clustergeometry object basing on a triangular @ref tri2d mesh 
 * and Raviart-Thomas functions.
 * 
 * @param rt @ref tet3drt0 object.
 * @param idx Array of indices (here: for the degrees of freedoms (edges)).
 * @returns Clustergeometry object.
 */
HEADER_PREFIX pclustergeometry 
build_tet3drt0_A_clustergeometry(pctet3drt0 rt, uint *idx);

/** @brief Create a @ref clustergeometry object for the clustering of the triangles.
 * 
 * Create a @ref clustergeometry object basing on a triangular @ref tri2d mesh 
 * and linear nodal basis functions.
 * 
 * @param rt @ref tet3drt0 object.
 * @param idx Array of indices (here: for the triangles).
 * @returns Clustergeometry object.
 */
HEADER_PREFIX pclustergeometry 
build_tet3drt0_B_clustergeometry(pctet3drt0 rt, uint *idx);

/** @}*/
#endif
