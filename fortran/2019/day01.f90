program day01
    implicit none


    integer, parameter :: max_modules = 256
    integer, parameter :: max_iters = 64

    integer :: nvalues
    integer :: i
    integer, dimension(max_modules) :: mass
    integer, dimension(max_modules,max_iters) :: fuels

    call read_stdin(mass, nvalues)

    ! Solve Part 1
    fuels(:,1) = mass / 3 - 2

    ! Solve Part 2
    do i=2,max_iters
        fuels(:,i) = max(fuels(:,i-1) / 3 - 2, 0)
        if (sum(fuels(:,i)) == 0) exit
    end do

    print *, 'Naive fuel required: ', sum(fuels(1:nvalues,1))
    print *, 'Total fuel required: ', sum(fuels(1:nvalues,:i))

contains

subroutine read_stdin(mass, nvalues)
    use, intrinsic :: iso_fortran_env, only : input_unit
    implicit none

    integer, intent(in out) :: mass(:)
    integer, intent(out) :: nvalues

    integer :: ios

    nvalues = 1
    do
        read(input_unit, *, iostat=ios) mass(nvalues)
        if (ios /= 0) exit
        nvalues = nvalues + 1
    end do
    nvalues = nvalues - 1
end subroutine read_stdin

end program day01