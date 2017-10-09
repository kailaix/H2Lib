cmake_minimum_required(VERSION 3.6)
project(H2Lib)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
#        Examples/example_amatrix_bem3d.c
#        Examples/example_dh2matrix.c
#        Examples/example_fem_p1_harith.c
#        Examples/example_fem_rt0_harith.c
#        Examples/example_h2matrix_bem3d.c
#        Examples/example_hmatrix_bem3d.c
#        Examples/example_visualize.c
        Library/aca.c
        Library/aca.h
        Library/amatrix.c
        Library/amatrix.h
        Library/avector.c
        Library/avector.h
        Library/basic.c
        Library/basic.h
        Library/bem2d.c
        Library/bem2d.h
        Library/bem3d.c
        Library/bem3d.h
        Library/blas.h
        Library/block.c
        Library/block.h
        Library/clsettings.h
        Library/cluster.c
        Library/cluster.h
        Library/clusterbasis.c
        Library/clusterbasis.h
        Library/clustergeometry.c
        Library/clustergeometry.h
        Library/clusteroperator.c
        Library/clusteroperator.h
        Library/curve2d.c
        Library/curve2d.h
        Library/dblock.c
        Library/dblock.h
        Library/dcluster.c
        Library/dcluster.h
        Library/dclusterbasis.c
        Library/dclusterbasis.h
        Library/dclusteroperator.c
        Library/dclusteroperator.h
        Library/ddcluster.c
        Library/ddcluster.h
        Library/dh2compression.c
        Library/dh2compression.h
        Library/dh2matrix.c
        Library/dh2matrix.h
        Library/duniform.c
        Library/duniform.h
        Library/eigensolvers.c
        Library/eigensolvers.h
        Library/factorizations.c
        Library/factorizations.h
        Library/gaussquad.c
        Library/gaussquad.h
        Library/h2arith.c
        Library/h2arith.h
        Library/h2compression.c
        Library/h2compression.h
        Library/h2matrix.c
        Library/h2matrix.h
        Library/h2update.c
        Library/h2update.h
        Library/harith.c
        Library/harith.h
        Library/harith2.c
        Library/harith2.h
        Library/hcoarsen.c
        Library/hcoarsen.h
        Library/helmholtzbem3d.c
        Library/helmholtzbem3d.h
        Library/helmholtzoclbem3d.c
        Library/helmholtzoclbem3d.h
        Library/hmatrix.c
        Library/hmatrix.h
        Library/krylov.c
        Library/krylov.h
        Library/krylovsolvers.c
        Library/krylovsolvers.h
        Library/laplacebem2d.c
        Library/laplacebem2d.h
        Library/laplacebem3d.c
        Library/laplacebem3d.h
        Library/laplaceoclbem3d.c
        Library/laplaceoclbem3d.h
        Library/macrosurface3d.c
        Library/macrosurface3d.h
        Library/matrixnorms.c
        Library/matrixnorms.h
        Library/oclbem3d.c
        Library/oclbem3d.h
        Library/opencl.c
        Library/opencl.h
        Library/parameters.c
        Library/parameters.h
        Library/realavector.c
        Library/realavector.h
        Library/rkmatrix.c
        Library/rkmatrix.h
        Library/settings.c
        Library/settings.h
        Library/simd.h
        Library/simd_avx.h
        Library/simd_sse2.h
        Library/singquad1d.c
        Library/singquad1d.h
        Library/singquad2d.c
        Library/singquad2d.h
        Library/sparsematrix.c
        Library/sparsematrix.h
        Library/sparsepattern.c
        Library/sparsepattern.h
        Library/surface3d.c
        Library/surface3d.h
        Library/tet3d.c
        Library/tet3d.h
        Library/tet3dp1.c
        Library/tet3dp1.h
        Library/tet3drt0.c
        Library/tet3drt0.h
        Library/tri2d.c
        Library/tri2d.h
        Library/tri2dp1.c
        Library/tri2dp1.h
        Library/tri2drt0.c
        Library/tri2drt0.h
        Library/truncation.c
        Library/truncation.h
        Library/uniform.c
        Library/uniform.h
        Library/visualize.c
        Library/visualize.h
#        Tests/test_amatrix.c
#        Tests/test_ddcluster.c
#        Tests/test_eigen.c
#        Tests/test_h2compression.c
#        Tests/test_h2matrix.c
#        Tests/test_helmholtzbem3d.c
#        Tests/test_helmholtzbem3d_ocl.c
#        Tests/test_hmatrix.c
#        Tests/test_krylov.c
#        Tests/test_krylovsolvers.c
        Tests/test_laplacebem2d.c
#        Tests/test_laplacebem3d.c
#        Tests/test_laplacebem3d_ocl.c
#        Tests/test_tet3d.c
#        Tests/test_tet3dp1.c
#        Tests/test_tet3drt0.c
#        Tests/test_tri2d.c
#        Tests/test_tri2dp1.c
#        Tests/test_tri2drt0.c
        )

include_directories(Library)

add_executable(H2Lib ${SOURCE_FILES})
target_link_libraries(H2Lib winmm )
