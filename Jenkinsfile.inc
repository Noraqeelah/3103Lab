pipeline {
	agent any
	stages {
		stage('Checkout SCM') {
			steps {

				cleanWs()
				checkout scm

			}
		}
		stage('Build') {
				steps {
						sh 'composer install'
					}
				}

		stage('Test') {
			steps {
                sh './vendor/bin/phpunit tests'
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
