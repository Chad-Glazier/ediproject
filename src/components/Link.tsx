import type { IconDefinition } from "@fortawesome/fontawesome-svg-core"
import styles from "./Link.module.css"
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome"

type LinkProps = {
	href: string
	icon?: IconDefinition
	text?: string
}

function Link({
	href, icon, text
}: LinkProps) {
	const target = href.startsWith("#") ? "_self" : "_blank"

	return <a href={href} target={target} className={styles.link}>
		{icon && <FontAwesomeIcon icon={icon} />}
		{icon && text && <>&nbsp;</>}
		{text}
		<span className={styles.underline}></span>
	</a>
}

export default Link
