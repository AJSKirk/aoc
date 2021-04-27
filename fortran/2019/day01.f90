program day01
    implicit none

    character(len=32) :: filename
    integer :: ios
    integer :: nvalues
    integer, dimension(256) :: mass
    integer, dimension(256) :: fuels

    ! Read in file
    call getarg(1, filename)
    open(unit=1, file=filename)
    nvalues = 1
    do
        read(1, *, iostat=ios) mass(nvalues)
        if (ios /= 0) then
            exit
        end if
        nvalues = nvalues + 1
    end do
    nvalues = nvalues - 1
    close(1)

    fuels = mass / 3 - 2
    print *, 'Total fuel required: ', sum(fuels(1:nvalues))

end program day01