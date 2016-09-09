#line 239 "funnelweb.fw"

 (make-face 'funnelweb-face)
 (set-face-foreground  'funnelweb-face "cadetblue")
 (copy-face 'funnelweb-face 'font-lock-keyword-face)


 (setq c++-font-lock-keywords
       (append c++-font-lock-keywords
               (list  '("@<.*@>" . funnelweb-face)
                      '("@p.*@>" . funnelweb-face)
                      '("@." . funnelweb-face))))
