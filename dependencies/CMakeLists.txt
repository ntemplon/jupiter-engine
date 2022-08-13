include(FetchContent)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY "https://github.com/SFML/SFML"
  GIT_TAG        2.5.1 # 2f11710abc5aa478503a7ff3f9e654bd2078ebab - it's supposedly faster to use the binary commit, but I choose readability
)

add_subdirectory(sfml)
