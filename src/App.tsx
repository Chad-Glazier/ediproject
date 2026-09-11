import styles from "./App.module.css"
import Link from "./components/Link"
import Logo from "./components/Logo"
import underConstructionGif from "./assets/img/under_construction.gif"

function App() {
    return (
        <main className={styles.main}>
            <div className={styles.overview}>
                <Logo />
                <p>
                    The EDI Project is an effort to study and improve programs that play the <Link href="https://en.wikipedia.org/wiki/Game_of_the_Amazons" text="Game of Amazons" />.                    
                </p>
            </div>
            <article className={styles.article}>
                <img 
                    src={underConstructionGif}
                    alt=""
                />
                <p>
                    This website is currently incomplete. In the interim, you should refer to the actively maintained <Link href="https://github.com/Chad-Glazier/edi" text="GitHub Repository" /> for details about the core EDI library and command-line tool. You can also read a written report about the first version of the EDI program <Link text="here" href="https://raw.githubusercontent.com/Chad-Glazier/edi/main/docs/EDI_Report.pdf" />.             
                </p>
            </article>
        </main>
    )
}

export default App
