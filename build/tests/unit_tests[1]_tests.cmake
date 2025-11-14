add_test([=[SampleTest.VectorBasics]=]  /media/jesusmontiel/Datos/Desarrollos/cpp-study/build/tests/unit_tests [==[--gtest_filter=SampleTest.VectorBasics]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SampleTest.VectorBasics]=]  PROPERTIES WORKING_DIRECTORY /media/jesusmontiel/Datos/Desarrollos/cpp-study/build/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  unit_tests_TESTS SampleTest.VectorBasics)
