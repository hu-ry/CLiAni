FROM archlinux

# Set Working Directory
WORKDIR /usr/src/clani

# Faster mirror for build process
RUN echo 'Server = https://mirror.pkgbuild.com/$repo/os/$arch' > /etc/pacman.d/mirrorlist

# Installing pkgs
RUN pacman -Suy --noconfirm --needed base base-devel cmake ncurses boost

# Cleaning pacman cache
RUN find /var/cache/pacman/ -type f -delete && cd /usr/src/clani

# Copy source code into image filesystem
COPY . .

# Building project
RUN cmake -E make_directory build
RUN cmake -E chdir build cmake ..
RUN cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" /usr/src/clani
RUN cmake --build /usr/src/clani/build --target clani -- -j 4

# Run Application
RUN echo "To run the application execute ./clani in the /usr/src/clani/build/ directory!"