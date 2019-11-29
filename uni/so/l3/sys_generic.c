int 
sys_khello(struct proc *p, void *v, register_t *retval)
{
    printf("%s\n", "hello");

    return 0;
}


int
sys_cpy_str(struct proc *p, void *v, register_t *retval)
{
    struct sys_cpy_str_args *uap = v;
    char *ksource = malloc(SCARG(uap, len), M_TEMP, M_WAITOK);

    copyinstr(SCARG(uap, source), ksource, SCARG(uap, len), NULL);
    copyoutstr(ksource, SCARG(uap, copy), SCARG(uap, len), NULL);
    
    free(ksource, M_TEMP, SCARG(uap, len));

    return 0;
}