echo "Running formatting and style checks...";
make style;
make check-style;

echo "Building Pantomime...";
make

echo "Done."
