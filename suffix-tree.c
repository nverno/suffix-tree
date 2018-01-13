/** @file suffix-tree.c
 * @brief suffix tree
 */
#include <emacs-module.h>

/* mandatory GPL symbol */
int plugin_is_GPL_compatible;

/* New emacs lisp function -- all functions exposed to emacs have this prototype */
static emacs_value
Fsuffix_tree(emacs_env *env, long nargs, emacs_value args[], void *data) {
    return env->make_integer(env, 42);
}

/* bind NAME to FUN. */
static void bind_function(emacs_env *env, const char *name, emacs_value Sfun) {
    /* Set the function cell of the symbol named NAME to SFUN using
       the 'fset' function */
    
    /* Convert the strings to symbols by interning them */
    emacs_value Qfset = env->intern(env, "fset");
    emacs_value Qsym = env->intern(env, name);
    
    /* Prepare the arguments array */
    emacs_value args[] = { Qsym, Sfun };
    
    /* Make the call (2 == nb of arguments) */
    env->funcall(env, Qfset, 2, args);
}

/* Provide FEATURE to emacs */
static void provide(emacs_env *env, const char *feature) {
    /* call 'provide' with FEATURE converted to a symbol */
    emacs_value Qfeat = env->intern(env, feature);
    emacs_value Qprovide = env->intern(env, "provide");
    emacs_value args[] = { Qfeat };
    
    env->funcall(env, Qprovide, 1, args);
}

int emacs_module_init(struct emacs_runtime *ert) {
    emacs_env *env = ert->get_environment(ert);
    
    /* create a lambda (returns an emacs_value) */
    emacs_value fun = env->make_function(
        env,
        0,                         /* min number args */
        0,                         /* max number args */
        Fsuffix_tree,              /* actual function pointer */
        "Test making suffix tree", /* doc */
        NULL);                     /* user pointer (data param in Fsuffix_tree) */
    
    bind_function(env, "suffix-tree", fun);
    provide(env, "suffix-tree");
    
    /* loaded successfully */
    return 0;
}
