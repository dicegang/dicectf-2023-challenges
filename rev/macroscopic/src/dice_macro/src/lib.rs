use proc_macro::TokenStream;
use syn::{parse_macro_input, Ident};

#[proc_macro]
pub fn dice(item: TokenStream) -> TokenStream {
    let flag = parse_macro_input!(item as Ident).to_string();
    let bitcounts = flag
        .bytes()
        .map(|c| (c, 8u8))
        .flat_map(|(mut c, mut c2)| {
            std::iter::from_fn(move || {
                if c2 == 0 {
                    None
                } else if c == 0 {
                    let res = c2;
                    c2 = 0;
                    Some(res)
                } else {
                    let mut res = c.leading_ones();
                    if res == 0 {
                        res = c.leading_zeros();
                    }
                    c <<= res;
                    c2 -= res as u8;
                    Some(res as u8)
                }
            })
        })
        .collect::<Vec<u8>>();
    format!("&{bitcounts:?}").parse().unwrap()
}
