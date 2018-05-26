open Ast_mapper;
open Ast_helper;
open Asttypes;
open Parsetree;
open Longident;

let rec print_ident = fun
| Lident(x) => { print_string("lid:"); print_string(x) }
| Ldot(y, x) => { print_string("ldo:"); print_ident(y); print_string(x) }
| Lapply(y, x) => { print_string("lap:"); print_ident(y); print_ident(x) };

let jsxz_mapper = argv => {
    {
        ...default_mapper,
        expr: (mapper, expr) => switch expr {
            | {
                pexp_attributes: [({txt: "JSX"}, _)],
                pexp_desc: Pexp_apply({
                    pexp_desc: Pexp_ident({txt: x})
                }, _)
            } =>
            print_ident(x);
            expr
            | _ => default_mapper.expr(mapper, expr)
        }
    }
};

let () = register("jsxz", jsxz_mapper);
