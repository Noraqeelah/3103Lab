pipeline {
	agent any
	stages {
		stage('Checkout SCM') {
			steps {
				git '/3103/3103Lab'
			}
		}

		stage('OWASP DependencyCheck') {
			steps {
				dependencyCheck additionalArguments: '--format HTML --format XML', odcInstallation: 'Default'
			}
		}
	}
	post {
		success {
			dependencyCheckPublisher pattern: 'dependency-check-report.xml'
			sh "sudo rm -R /var/127.0.0.1:8080/* /var/127.0.0.1:8080/.* || true"
		}
	}
}
