include(cmake/CPM.cmake)

function(logvalcpp_setup_dependencies)

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage("gh:catchorg/Catch2@3.3.2")
  endif()

endfunction()
